# SPDX-License-Identifier: Apache-2.0 OR MIT

set(LIBBZ2_VERSION "1.1.0")
set(LIBBZ2_SRCDIR "${CMAKE_SOURCE_DIR}/extern/permissive/bzip2")

set(LIBBZ2_SOURCES
    ${LIBBZ2_SRCDIR}/blocksort.c
    ${LIBBZ2_SRCDIR}/huffman.c
    ${LIBBZ2_SRCDIR}/crctable.c
    ${LIBBZ2_SRCDIR}/randtable.c
    ${LIBBZ2_SRCDIR}/compress.c
    ${LIBBZ2_SRCDIR}/decompress.c
    ${LIBBZ2_SRCDIR}/bzlib.c
)

add_library("libbz2" SHARED "${LIBBZ2_SOURCES}")
target_include_directories("libbz2" PRIVATE .)
target_compile_options("libbz2" PRIVATE -Wno-unused-parameter)

add_library("libbz2static" STATIC "${LIBBZ2_SOURCES}")
target_include_directories("libbz2static" PRIVATE .)
target_compile_options("libbz2static" PRIVATE -Wno-unused-parameter)

set_target_properties("libbz2" "libbz2static" PROPERTIES OUTPUT_NAME "bz2"
                                                         C_CLANG_TIDY "")
