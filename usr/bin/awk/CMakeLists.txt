# SPDX-License-Identifier: Apache-2.0 OR ISC

set(AWK_VERSION "20221215")
set(AWK_SRCDIR "${CMAKE_SOURCE_DIR}/extern/permissive/one-true-awk")

# yacc
add_custom_command(
  OUTPUT awkgram.tab.c awkgram.tab.h

  COMMAND yacc -d -b awkgram 
          "${AWK_SRCDIR}/awkgram.y"

  DEPENDS ${AWK_SRCDIR}/awkgram.y
          ${AWK_SRCDIR}/awk.h
          ${AWK_SRCDIR}/proto.h
)

# awk itself
set(AWK_SOURCES
    awkgram.tab.c
    awkgram.tab.h
    proctab.c
    ${AWK_SRCDIR}/awk.h
    ${AWK_SRCDIR}/b.c
    ${AWK_SRCDIR}/lex.c
    ${AWK_SRCDIR}/lib.c
    ${AWK_SRCDIR}/main.c
    ${AWK_SRCDIR}/parse.c
    ${AWK_SRCDIR}/proto.h
    ${AWK_SRCDIR}/run.c
    ${AWK_SRCDIR}/tran.c
)
add_executable("awk" ${AWK_SOURCES})
target_compile_options("awk" PRIVATE -Wno-unused-parameter
                                     -Wno-unused-but-set-variable)
target_include_directories("awk"
                           PRIVATE ${AWK_SRCDIR}
                                   ${CMAKE_BINARY_DIR}/usr/bin/awk)

# link to libm because glibc is dumb and has it as a separate shared library
target_link_libraries("awk" m)
