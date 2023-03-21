# SPDX-License-Identifier: Apache-2.0 OR ISC

set(BYACC_VERSION "20230219")
set(BYACC_SRCDIR  "${CMAKE_SOURCE_DIR}/extern/publicdomain/byacc")

set(BYACC_SOURCES
    config.h
    ${BYACC_SRCDIR}/defs.h
    ${BYACC_SRCDIR}/closure.c
    ${BYACC_SRCDIR}/error.c
    ${BYACC_SRCDIR}/graph.c
    ${BYACC_SRCDIR}/lalr.c
    ${BYACC_SRCDIR}/lr0.c
    ${BYACC_SRCDIR}/main.c
    ${BYACC_SRCDIR}/mkpar.c
    ${BYACC_SRCDIR}/mstring.c
    ${BYACC_SRCDIR}/output.c
    ${BYACC_SRCDIR}/reader.c
    ${BYACC_SRCDIR}/btyaccpar.c
    ${BYACC_SRCDIR}/symtab.c
    ${BYACC_SRCDIR}/verbose.c
    ${BYACC_SRCDIR}/warshall.c
)

add_executable("byacc" ${BYACC_SOURCES})

target_compile_definitions("byacc" PRIVATE HAVE_CONFIG_H YYPATCH=${BYACC_VERSION})
target_include_directories("byacc" PRIVATE ${BYACC_SRCDIR} .)
