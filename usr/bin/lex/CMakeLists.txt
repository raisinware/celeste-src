# SPDX-License-Identifier: Apache-2.0 OR ISC

set(FLEX_VERSION "2.6.4")
set(FLEX_SRCDIR  "${CMAKE_SOURCE_DIR}/extern/permissive/flex/src")

set(FLEX_SOURCES
    config.h
    gettext.h
    stage1scan.c
    ${FLEX_SRCDIR}/buf.c
	${FLEX_SRCDIR}/ccl.c
	${FLEX_SRCDIR}/dfa.c
	${FLEX_SRCDIR}/ecs.c
	${FLEX_SRCDIR}/filter.c
	${FLEX_SRCDIR}/flexdef.h
	${FLEX_SRCDIR}/flexint.h
	${FLEX_SRCDIR}/gen.c
	${FLEX_SRCDIR}/main.c
	${FLEX_SRCDIR}/misc.c
	${FLEX_SRCDIR}/nfa.c
	${FLEX_SRCDIR}/options.c
	${FLEX_SRCDIR}/options.h
	${FLEX_SRCDIR}/parse.c
	${FLEX_SRCDIR}/regex.c
	${FLEX_SRCDIR}/scanflags.c
	${FLEX_SRCDIR}/scanopt.c
	${FLEX_SRCDIR}/scanopt.h
	${FLEX_SRCDIR}/skel.c
	${FLEX_SRCDIR}/sym.c
	${FLEX_SRCDIR}/tables.c
	${FLEX_SRCDIR}/tables.h
	${FLEX_SRCDIR}/tables_shared.c
	${FLEX_SRCDIR}/tables_shared.h
	${FLEX_SRCDIR}/tblcmp.c
	${FLEX_SRCDIR}/version.h
	${FLEX_SRCDIR}/yylex.c
)

add_executable("flex" ${FLEX_SOURCES})

target_compile_definitions("flex" PRIVATE HAVE_CONFIG_H)
target_include_directories("flex" PRIVATE ${FLEX_SRCDIR} .)

# link to libm because glibc is dumb and has it as a separate shared library
target_link_libraries("flex" m)
