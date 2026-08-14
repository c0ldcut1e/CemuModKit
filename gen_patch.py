from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

for candidate in (Path("/tmp/capstone_pkgs"),):
    if candidate.exists():
        sys.path.insert(0, str(candidate))

try:
    from capstone import CS_ARCH_PPC, CS_MODE_32, CS_MODE_BIG_ENDIAN, Cs
except ImportError:
    Cs = None

IMPORTS_FILE = Path(__file__).parent / "imports.txt"

PROLOGUE_HEADER = [
    "[Wrapper]",
    "moduleMatches = {module_matches}",
    "",
    "0x02F37154 = b _start",
    "",
    "0x104D4DD8 = .uint _code",
    "0x104D4DDC = .uint 0x0",
    "",
    ".origin = codecave",
    "",
    "# .text",
    "_code:",
]

EPILOGUE_LINES = [
    ".uint 0x00000000",
    "",
    "_imports:",
]

BOOTSTRAP_LINES = [
    "",
    "_start:",
    "bctrl",
    "stwu r1, -0xC0(r1)",
    "stw r0, 0x18(r1)",
    "mflr r0",
    "stw r0, 0x08(r1)",
    "mfctr r0",
    "stw r0, 0x0C(r1)",
    ".uint 0x7C000026",
    "stw r0, 0x10(r1)",
    ".uint 0x7C0102A6",
    "stw r0, 0x14(r1)",
    "stw r2, 0x20(r1)",
    "stw r3, 0x24(r1)",
    "stw r4, 0x28(r1)",
    "stw r5, 0x2C(r1)",
    "stw r6, 0x30(r1)",
    "stw r7, 0x34(r1)",
    "stw r8, 0x38(r1)",
    "stw r9, 0x3C(r1)",
    "stw r10, 0x40(r1)",
    "stw r11, 0x44(r1)",
    "stw r12, 0x48(r1)",
    "stw r13, 0x4C(r1)",
    "stfd f0, 0x50(r1)",
    "stfd f1, 0x58(r1)",
    "stfd f2, 0x60(r1)",
    "stfd f3, 0x68(r1)",
    "stfd f4, 0x70(r1)",
    "stfd f5, 0x78(r1)",
    "stfd f6, 0x80(r1)",
    "stfd f7, 0x88(r1)",
    "stfd f8, 0x90(r1)",
    "stfd f9, 0x98(r1)",
    "stfd f10, 0xA0(r1)",
    "stfd f11, 0xA8(r1)",
    "stfd f12, 0xB0(r1)",
    "stfd f13, 0xB8(r1)",
    "lis r3, _imports@ha",
    "addi r3, r3, _imports@l",
    "lis r12, _code@ha",
    "addi r12, r12, _code@l",
    "mtctr r12",
    "bctrl",
    "lfd f0, 0x50(r1)",
    "lfd f1, 0x58(r1)",
    "lfd f2, 0x60(r1)",
    "lfd f3, 0x68(r1)",
    "lfd f4, 0x70(r1)",
    "lfd f5, 0x78(r1)",
    "lfd f6, 0x80(r1)",
    "lfd f7, 0x88(r1)",
    "lfd f8, 0x90(r1)",
    "lfd f9, 0x98(r1)",
    "lfd f10, 0xA0(r1)",
    "lfd f11, 0xA8(r1)",
    "lfd f12, 0xB0(r1)",
    "lfd f13, 0xB8(r1)",
    "lwz r2, 0x20(r1)",
    "lwz r3, 0x24(r1)",
    "lwz r4, 0x28(r1)",
    "lwz r5, 0x2C(r1)",
    "lwz r6, 0x30(r1)",
    "lwz r7, 0x34(r1)",
    "lwz r8, 0x38(r1)",
    "lwz r9, 0x3C(r1)",
    "lwz r10, 0x40(r1)",
    "lwz r11, 0x44(r1)",
    "lwz r12, 0x48(r1)",
    "lwz r13, 0x4C(r1)",
    "lwz r0, 0x14(r1)",
    ".uint 0x7C0103A6",
    "lwz r0, 0x10(r1)",
    ".uint 0x7C0FF120",
    "lwz r0, 0x0C(r1)",
    "mtctr r0",
    "lwz r0, 0x08(r1)",
    "mtlr r0",
    "lwz r0, 0x18(r1)",
    "addi r1, r1, 0xC0",
    "b 0x02F37158",
]

TEXT_SYMBOL_TYPES = {"T", "t", "W", "w"}
RESERVED_LABELS = {"_code", "_imports", "_start"}


def load_imports(path: Path) -> list[str]:
    entries: list[str] = []
    if not path.exists():
        return entries
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.split("#", 1)[0].strip()
        if not line:
            continue
        parts = line.split(".", 1)
        if len(parts) == 2 and parts[0] and parts[1]:
            entries.append(f"{parts[0].strip()}.{parts[1].strip()}")
        else:
            print(
                f"[gen_patch] skipping malformed imports line: {raw!r}",
                file=sys.stderr,
            )
    return entries


@dataclass(frozen=True)
class TextSymbol:
    name: str
    address: int
    offset: int


@dataclass(frozen=True)
class TextInstruction:
    address: int
    offset: int
    bytes_hex: str
    asm: str


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("input_bin", help="Path to the extracted .text section binary")
    parser.add_argument("output_asm", help="Path to the generated ASM file")
    parser.add_argument("module_matches", help="moduleMatches value for the wrapper")
    parser.add_argument("--elf", type=Path)
    parser.add_argument("--nm-tool", default="nm")
    parser.add_argument("--objdump-tool", default="objdump")
    parser.add_argument(
        "--plain", action="store_true", help="Unused, kept for compatibility."
    )
    return parser.parse_args()


def display_path(path: Path) -> str:
    try:
        resolved_path = path.resolve()
        resolved_cwd = Path.cwd().resolve()
        if resolved_path.is_relative_to(resolved_cwd):
            return str(resolved_path.relative_to(resolved_cwd))
        return str(resolved_path)
    except (OSError, RuntimeError, ValueError):
        return str(path)


def chunk_to_uint_line(chunk: bytes) -> str:
    return f".uint 0x{chunk.ljust(4, b'\x00').hex().upper()}"


def run_tool(args: list[str]) -> str:
    return subprocess.run(args, check=True, capture_output=True, text=True).stdout


def read_text_section_info(elf_path: Path, objdump_tool: str) -> tuple[int, int]:
    output = run_tool([objdump_tool, "-h", str(elf_path)])
    for line in output.splitlines():
        match = re.match(
            r"^\s*\d+\s+\.text\s+([0-9A-Fa-f]+)\s+([0-9A-Fa-f]+)\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+\S+",
            line,
        )
        if match:
            return int(match.group(2), 16), int(match.group(1), 16)
    raise ValueError(f"Unable to locate .text section in {elf_path}")


def load_text_symbols(
    elf_path: Path | None,
    nm_tool: str,
    objdump_tool: str,
    text_size: int,
) -> list[TextSymbol]:
    if elf_path is None or not elf_path.exists():
        return []
    try:
        text_start, elf_text_size = read_text_section_info(elf_path, objdump_tool)
        text_limit = text_start + min(text_size, elf_text_size)
        output = run_tool([nm_tool, "-n", "--defined-only", str(elf_path)])
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        print(
            f"[gen_patch] skipping symbols ({exc.__class__.__name__})",
            file=sys.stderr,
        )
        return []

    symbols: list[TextSymbol] = []
    for line in output.splitlines():
        match = re.match(r"^([0-9A-Fa-f]+)\s+([A-Za-z])\s+(.+)$", line)
        if not match:
            continue
        address = int(match.group(1), 16)
        symbol_type = match.group(2)
        name = match.group(3).strip()
        if symbol_type not in TEXT_SYMBOL_TYPES:
            continue
        if not (text_start <= address < text_limit):
            continue
        symbols.append(
            TextSymbol(name=name, address=address, offset=address - text_start)
        )
    return symbols


def find_code_end_offset(
    elf_path: Path | None,
    nm_tool: str,
    objdump_tool: str,
    text_size: int,
) -> int:
    if elf_path is None or not elf_path.exists():
        return text_size
    try:
        text_start, _ = read_text_section_info(elf_path, objdump_tool)
        output = run_tool([nm_tool, "--defined-only", str(elf_path)])
    except (OSError, ValueError, subprocess.CalledProcessError):
        return text_size
    for line in output.splitlines():
        match = re.match(r"^([0-9A-Fa-f]+)\s+\S\s+_code_end$", line)
        if match:
            return int(match.group(1), 16) - text_start
    return text_size


def build_symbol_index(symbols: list[TextSymbol]) -> dict[int, list[TextSymbol]]:
    index: dict[int, list[TextSymbol]] = {}
    for symbol in symbols:
        index.setdefault(symbol.offset, []).append(symbol)
    return index


def normalize_instruction_text(text: str) -> str:
    text = re.sub(r"\s+", " ", text.strip())

    def normalize_hex_address(match: re.Match[str]) -> str:
        return f"0x{int(match.group(1), 16):08X}"

    return re.sub(
        r"\b(?:0x)?([0-9A-Fa-f]{6,})\b(?=(?:\s*<)|(?:\s*$))",
        normalize_hex_address,
        text,
    )


def load_text_instructions(
    elf_path: Path | None,
    objdump_tool: str,
    text_section: bytes,
    code_size: int | None = None,
) -> list[TextInstruction]:
    if Cs is None or elf_path is None or not elf_path.exists():
        return []
    try:
        text_start, _ = read_text_section_info(elf_path, objdump_tool)
    except (OSError, ValueError, subprocess.CalledProcessError) as exc:
        print(
            f"[gen_patch] skipping disassembly ({exc.__class__.__name__})",
            file=sys.stderr,
        )
        return []

    if code_size is None:
        code_size = len(text_section)
    code_bytes = text_section[:code_size]

    md = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)  # type: ignore
    instructions: list[TextInstruction] = []
    for insn in md.disasm(code_bytes, text_start):
        asm = normalize_instruction_text(f"{insn.mnemonic} {insn.op_str}".strip())
        instructions.append(
            TextInstruction(
                address=insn.address,
                offset=insn.address - text_start,
                bytes_hex=insn.bytes.hex(),
                asm=asm,
            )
        )
    return instructions


def build_instruction_index(
    instructions: list[TextInstruction],
) -> dict[int, TextInstruction]:
    return {i.offset: i for i in instructions}


def build_symbol_address_index(symbols: list[TextSymbol]) -> dict[int, list[str]]:
    index: dict[int, list[str]] = {}
    for symbol in symbols:
        index.setdefault(symbol.address, []).append(symbol.name)
    return index


def make_safe_label(name: str) -> str:
    label = re.sub(r"[^A-Za-z0-9_]", "_", name)
    if not label:
        label = "sym"
    if label[0].isdigit():
        label = "_" + label
    return label


def build_symbol_label_map(symbols: list[TextSymbol]) -> dict[TextSymbol, str]:
    base_counts: dict[str, int] = {}
    for symbol in symbols:
        base = make_safe_label(symbol.name)
        base_counts[base] = base_counts.get(base, 0) + 1

    labels: dict[TextSymbol, str] = {}
    used_labels: set[str] = set(RESERVED_LABELS)
    for symbol in symbols:
        base = make_safe_label(symbol.name)
        label = base
        if base_counts[base] > 1 or label in used_labels:
            label = f"{base}_{symbol.address:08X}"

        unique_label = label
        suffix = 2
        while unique_label in used_labels:
            unique_label = f"{label}_{suffix}"
            suffix += 1

        used_labels.add(unique_label)
        labels[symbol] = unique_label

    return labels


def format_symbol_label(
    symbol: TextSymbol, symbol_label_map: dict[TextSymbol, str]
) -> str:
    return f"{symbol_label_map[symbol]}:"


def annotate_branch_targets(
    asm: str, symbol_address_index: dict[int, list[str]]
) -> str:
    if not asm.split(" ", 1)[0].startswith("b"):
        return asm

    def replace_target(match: re.Match[str]) -> str:
        address = int(match.group(1), 16)
        names = symbol_address_index.get(address)
        if not names:
            return f"0x{address:08X}"
        return f"0x{address:08X} <{'/'.join(names)}>"

    return re.sub(r"\b0x([0-9A-F]{8})\b", replace_target, asm, count=1)


def format_instruction_comment(
    instruction: TextInstruction,
    symbol_address_index: dict[int, list[str]],
) -> str:
    asm = annotate_branch_targets(instruction.asm, symbol_address_index)
    return f"{asm}"


def format_code_lines(
    text_section: bytes,
    symbols: list[TextSymbol],
    instructions: list[TextInstruction],
    code_size: int | None = None,
    text_start: int = 0,
) -> list[str]:
    code_lines: list[str] = []
    symbol_index = build_symbol_index(symbols)
    symbol_label_map = build_symbol_label_map(symbols)
    instruction_index = build_instruction_index(instructions)
    symbol_address_index = build_symbol_address_index(symbols)
    if code_size is None:
        code_size = len(text_section)

    for offset in range(0, len(text_section), 4):
        chunk = text_section[offset : offset + 4]
        if offset in symbol_index:
            if code_lines and code_lines[-1] != "":
                code_lines.append("")
            code_lines.extend(
                format_symbol_label(s, symbol_label_map) for s in symbol_index[offset]
            )
        instruction = instruction_index.get(offset)
        line = chunk_to_uint_line(chunk)
        if instruction is not None:
            line = f"{line} # {format_instruction_comment(instruction, symbol_address_index)}"
        code_lines.append(line)

    return code_lines


def build_patch_contents(
    text_section: bytes,
    module_matches: str,
    symbols: list[TextSymbol],
    instructions: list[TextInstruction],
    imports: list[str],
    code_size: int | None = None,
    text_start: int = 0,
) -> str:
    lines = [line.format(module_matches=module_matches) for line in PROLOGUE_HEADER]
    lines.extend(
        format_code_lines(text_section, symbols, instructions, code_size, text_start)
    )
    lines.extend(EPILOGUE_LINES)
    lines.extend(f".uint import.{entry}" for entry in imports)
    lines.extend(BOOTSTRAP_LINES)
    return "\n".join(lines) + "\n"


def atomic_write_text(output_path: Path, contents: str) -> None:
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(
        "w",
        encoding="utf-8",
        dir=output_path.parent,
        delete=False,
        newline="\n",
    ) as handle:
        temp_path = Path(handle.name)
        handle.write(contents)
        handle.flush()
        os.fsync(handle.fileno())
    temp_path.replace(output_path)


def main() -> int:
    args = parse_args()

    imports = load_imports(IMPORTS_FILE)
    if not imports:
        print(
            f"[gen_patch] no imports found in {IMPORTS_FILE}, skipping", file=sys.stderr
        )

    text_section = Path(args.input_bin).read_bytes()
    symbols = load_text_symbols(
        args.elf, args.nm_tool, args.objdump_tool, len(text_section)
    )
    code_size = find_code_end_offset(
        args.elf, args.nm_tool, args.objdump_tool, len(text_section)
    )
    instructions = load_text_instructions(
        args.elf, args.objdump_tool, text_section, code_size
    )

    text_start = 0
    if args.elf and args.elf.exists():
        try:
            text_start, _ = read_text_section_info(args.elf, args.objdump_tool)
        except (OSError, ValueError, subprocess.CalledProcessError):
            pass

    contents = build_patch_contents(
        text_section,
        args.module_matches,
        symbols,
        instructions,
        imports,
        code_size,
        text_start,
    )
    atomic_write_text(Path(args.output_asm), contents)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
