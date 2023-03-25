# SPDX-License-Identifier: Apache-2.0 OR ISC

set(GMAKE_VERSION "4.4.1")
set(GMAKE_SRCDIR "${CMAKE_SOURCE_DIR}/extern/restrictive/gmake/src")
set(GMAKE_LIBDIR "${CMAKE_SOURCE_DIR}/extern/restrictive/gmake/lib")

set(GMAKE_SOURCES
    config.h
    gettext.h
    gmakeglob_impl.c
    ${GMAKE_SRCDIR}/ar.c 
    ${GMAKE_SRCDIR}/arscan.c 
    ${GMAKE_SRCDIR}/commands.c 
    ${GMAKE_SRCDIR}/default.c 
    ${GMAKE_SRCDIR}/dir.c 
    ${GMAKE_SRCDIR}/expand.c 
    ${GMAKE_SRCDIR}/file.c 
    ${GMAKE_SRCDIR}/function.c
    ${GMAKE_SRCDIR}/hash.c 
    ${GMAKE_SRCDIR}/implicit.c 
    ${GMAKE_SRCDIR}/job.c 
    ${GMAKE_SRCDIR}/load.c 
    ${GMAKE_SRCDIR}/loadapi.c 
    ${GMAKE_SRCDIR}/main.c 
    ${GMAKE_SRCDIR}/misc.c 
    ${GMAKE_SRCDIR}/output.c 
    ${GMAKE_SRCDIR}/posixos.c
    ${GMAKE_SRCDIR}/read.c 
    ${GMAKE_SRCDIR}/remake.c 
    ${GMAKE_SRCDIR}/rule.c 
    ${GMAKE_SRCDIR}/shuffle.c 
    ${GMAKE_SRCDIR}/signame.c 
    ${GMAKE_SRCDIR}/strcache.c 
    ${GMAKE_SRCDIR}/variable.c 
    ${GMAKE_SRCDIR}/vpath.c
    ${GMAKE_LIBDIR}/findprog-in.c
    ${GMAKE_LIBDIR}/concat-filename.c
)

add_executable("gmake" ${GMAKE_SOURCES})
target_compile_options("gmake" PRIVATE -Wno-constant-logical-operand
                                       -Wno-unused-parameter)
target_include_directories("gmake" PRIVATE ${GMAKE_SRCDIR} . ${GMAKE_LIBDIR})
