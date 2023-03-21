# SPDX-License-Identifier: Apache-2.0 OR ISC

# yacc
add_custom_command(
  OUTPUT awkgram.tab.c awkgram.tab.h

  COMMAND yacc -d -b awkgram 
          ${CMAKE_SOURCE_DIR}/contrib/one-true-awk/awkgram.y

  DEPENDS ../../../contrib/one-true-awk/awkgram.y
          ../../../contrib/one-true-awk/awk.h
          ../../../contrib/one-true-awk/proto.h
)

# host tool to generate proctab.c
# TODO: make sure this only builds on host
set(_MAKETAB_SOURCES
    awkgram.tab.h
    ../../../contrib/one-true-awk/maketab.c
)
add_executable("_maketab" EXCLUDE_FROM_ALL ${_MAKETAB_SOURCES})
target_include_directories("_maketab" PRIVATE ${CMAKE_BINARY_DIR}/usr/bin/awk)
add_custom_command(
  OUTPUT proctab.c

  COMMAND ${CMAKE_SOURCE_DIR}/usr/bin/awk/maketab.sh ${CMAKE_BINARY_DIR}

  DEPENDS _maketab awkgram.tab.h maketab.sh
)

# awk itself
set(AWK_SOURCES
    awkgram.tab.c
    awkgram.tab.h
    proctab.c
    ../../../contrib/one-true-awk/awk.h
    ../../../contrib/one-true-awk/b.c
    ../../../contrib/one-true-awk/lex.c
    ../../../contrib/one-true-awk/lib.c
    ../../../contrib/one-true-awk/main.c
    ../../../contrib/one-true-awk/parse.c
    ../../../contrib/one-true-awk/proto.h
    ../../../contrib/one-true-awk/run.c
    ../../../contrib/one-true-awk/tran.c
)
add_executable("awk" ${AWK_SOURCES})
target_include_directories("awk"
                           PRIVATE ../../../contrib/one-true-awk/
                                   ${CMAKE_BINARY_DIR}/usr/bin/awk)
target_link_libraries("awk" m) # i hate glibc
