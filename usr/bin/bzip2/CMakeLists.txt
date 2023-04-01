# SPDX-License-Identifier: Apache-2.0 OR MIT

set(BZIP2_SRCDIR "${CMAKE_SOURCE_DIR}/extern/permissive/bzip2")

add_executable("bzip2" ${BZIP2_SRCDIR}/bzip2.c)

target_compile_definitions("bzip2" PRIVATE BZ_UNIX=1)
set_target_properties("bzip2" PROPERTIES C_CLANG_TIDY "")
target_compile_options("bzip2" PRIVATE -Wno-constant-logical-operand
                                       -Wno-unused-parameter)
target_link_libraries("bzip2" libbz2)
