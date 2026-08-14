cmake_minimum_required(VERSION 3.21)

if(NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPRO")
endif()
if(NOT DEFINED ENV{DEVKITPPC})
    message(FATAL_ERROR "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif()

set(DEVKITPRO "$ENV{DEVKITPRO}")
set(DEVKITPPC "$ENV{DEVKITPPC}")
set(PORTLIBS  "${DEVKITPRO}/portlibs/ppc")

set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR powerpc)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Pass the object list to the linker via a response file so a failed link prints
# "@objects.rsp" instead of ~400 object paths, keeping linker errors readable.
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1)
set(CMAKE_C_USE_RESPONSE_FILE_FOR_OBJECTS   1)
set(CMAKE_NINJA_FORCE_RESPONSE_FILE ON CACHE INTERNAL "")

set(_prefix "${DEVKITPPC}/bin/powerpc-eabi-")
set(CMAKE_C_COMPILER   "${_prefix}gcc")
set(CMAKE_CXX_COMPILER "${_prefix}g++")
set(CMAKE_ASM_COMPILER "${_prefix}gcc")
set(CMAKE_AR           "${_prefix}ar")
set(CMAKE_OBJCOPY      "${_prefix}objcopy")
set(CMAKE_OBJDUMP      "${_prefix}objdump")
set(CMAKE_NM           "${_prefix}nm")

project(CemuModKit C CXX)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(TARGET         CemuModKit)
set(MODULE_MATCHES "0x867317DE,0x6237F45C,0x90112329")

set(DEBUG_LEVEL ON CACHE STRING "Debug level: OFF, ON, or VERBOSE")
set_property(CACHE DEBUG_LEVEL PROPERTY STRINGS OFF ON VERBOSE)

foreach(_cfg "" _DEBUG _RELEASE _MINSIZEREL _RELWITHDEBINFO)
    set(CMAKE_C_FLAGS${_cfg} "")
    set(CMAKE_CXX_FLAGS${_cfg} "")
endforeach()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.c"
     "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(FILTER SRC_FILES EXCLUDE REGEX "/src/lib/boost/")

add_executable(${TARGET} ${SRC_FILES})

set_target_properties(${TARGET} PROPERTIES
    OUTPUT_NAME              "${TARGET}"
    SUFFIX                   ".elf"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
    C_STANDARD               17
    C_EXTENSIONS             OFF
    CXX_STANDARD             20
    CXX_EXTENSIONS           OFF)

target_compile_options(${TARGET} PRIVATE
    -Wall -Wextra -fdiagnostics-color=always
    -mrvl -mcpu=750 -meabi -mhard-float -ffast-math
    -fshort-wchar -finline -fdata-sections -ffunction-sections
    -fno-optimize-sibling-calls -Os
    $<$<NOT:$<STREQUAL:${DEBUG_LEVEL},OFF>>:-g>)

target_compile_definitions(${TARGET} PRIVATE
    _GNU_SOURCE
    $<$<COMPILE_LANGUAGE:CXX>:FMT_HEADER_ONLY FMT_USE_LOCALE=0 FMT_USE_EXCEPTIONS=0 FMT_WIIU_OSREPORT=1>
    $<$<NOT:$<STREQUAL:${DEBUG_LEVEL},OFF>>:DEBUG>
    $<$<STREQUAL:${DEBUG_LEVEL},VERBOSE>:VERBOSE_DEBUG>)

set(_gcc_dir "${DEVKITPPC}/lib/gcc/powerpc-eabi/${CMAKE_C_COMPILER_VERSION}")

target_include_directories(${TARGET} PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/src/cut"
    "${CMAKE_SOURCE_DIR}/src/lib/mc")

target_include_directories(${TARGET} SYSTEM PRIVATE
    "${CMAKE_SOURCE_DIR}/src/lib"
    "${DEVKITPRO}/wut/include"
    "${DEVKITPRO}/libogc/include"
    "${DEVKITPPC}/lib/include"
    "${_gcc_dir}/include"
    "${PORTLIBS}/include"
    "${PORTLIBS}/include/freetype2")

target_link_directories(${TARGET} PRIVATE
    "${DEVKITPPC}/lib"
    "${_gcc_dir}/lib"
    "${DEVKITPRO}/libogc/lib/wii"
    "${PORTLIBS}/lib")

target_link_libraries(${TARGET} PRIVATE z vorbisidec ogg)

target_link_options(${TARGET} PRIVATE
    -n -T "${CMAKE_SOURCE_DIR}/link.ld"
    "-Wl,-Map,${TARGET}.elf.map"
    -Wl,--gc-sections
    -Wl,--wrap=_malloc_r
    -Wl,--wrap=_free_r
    -Wl,--wrap=_realloc_r
    -Wl,--wrap=_calloc_r
    -Wl,--wrap=_memalign_r
    -Wl,--wrap=_mallinfo_r
    -Wl,--wrap=_malloc_stats_r
    -Wl,--wrap=_mallopt_r
    -Wl,--wrap=_malloc_usable_size_r
    -Wl,--wrap=_valloc_r
    -Wl,--wrap=_pvalloc_r
    -Wl,--wrap=_malloc_trim_r)

set_target_properties(${TARGET} PROPERTIES LINK_DEPENDS "${CMAKE_SOURCE_DIR}/link.ld")

set(PATCH_ASM "${CMAKE_SOURCE_DIR}/GraphicPack/patch_${TARGET}.asm")

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_SOURCE_DIR}/GraphicPack"
    COMMAND "${CMAKE_OBJCOPY}" --only-section=.text
            "$<TARGET_FILE:${TARGET}>" -O binary "${CMAKE_BINARY_DIR}/.text.bin"
    COMMAND "${Python3_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/gen_patch.py"
            "${CMAKE_BINARY_DIR}/.text.bin"
            "${PATCH_ASM}"
            "${MODULE_MATCHES}"
            --elf "$<TARGET_FILE:${TARGET}>"
            --nm-tool "${CMAKE_NM}"
            --objdump-tool "${CMAKE_OBJDUMP}"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    COMMENT "generating patch_${TARGET}.asm ...")
