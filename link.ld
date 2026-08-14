OUTPUT_ARCH(powerpc)
ENTRY(entry)

MEMORY {
  TEXT_MEM : ORIGIN = 0x01800000, LENGTH = 0x10000000
}

SECTIONS {
  .text : {
    *(.text.entry)
    *(.entry)
    *(.text)
    *(.text.*)
    *(.gcc_except_table)
    *(.gcc_except_table.*)
    _code_end = .;
    *(.rodata)
    *(.rodata.*)
    *(.sdata)
    *(.sdata.*)
    *(.sdata2)
    *(.sdata2.*)
    *(.data)
    *(.data.*)
    *(.bss)
    *(.bss.*)
    *(.sbss)
    *(.sbss.*)
    *(.ext)
    *(.ext.*)
    data_end = .;
    __end__ = .;
  } > TEXT_MEM
}
