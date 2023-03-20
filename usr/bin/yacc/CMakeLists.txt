# SPDX-License-Identifier: Apache-2.0 OR ISC

set(BYACC_VERSION "20230219")

set(BYACC_SOURCES
    config.h
    ../../../contrib/byacc/defs.h
    ../../../contrib/byacc/closure.c
    ../../../contrib/byacc/error.c
    ../../../contrib/byacc/graph.c
    ../../../contrib/byacc/lalr.c
    ../../../contrib/byacc/lr0.c
    ../../../contrib/byacc/main.c
    ../../../contrib/byacc/mkpar.c
    ../../../contrib/byacc/mstring.c
    ../../../contrib/byacc/output.c
    ../../../contrib/byacc/reader.c
    ../../../contrib/byacc/btyaccpar.c
    ../../../contrib/byacc/symtab.c
    ../../../contrib/byacc/verbose.c
    ../../../contrib/byacc/warshall.c
)

add_executable("byacc" ${BYACC_SOURCES})

target_compile_definitions("byacc" PRIVATE HAVE_CONFIG_H YYPATCH=${BYACC_VERSION})
target_include_directories("byacc" PRIVATE ../../../contrib/byacc/ .)
