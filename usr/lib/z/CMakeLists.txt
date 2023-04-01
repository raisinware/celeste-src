# SPDX-License-Identifier: Apache-2.0 OR ISC

set(ZLIB_VERSION "1.2.13")
set(ZLIB_SRCDIR "${CMAKE_SOURCE_DIR}/extern/permissive/zlib")

set(ZLIB_PUBLIC_HDRS
    zconf.h
    ${ZLIB_SRCDIR}/zlib.h
)
set(ZLIB_PRIVATE_HDRS
    ${ZLIB_SRCDIR}/crc32.h
    ${ZLIB_SRCDIR}/deflate.h
    ${ZLIB_SRCDIR}/gzguts.h
    ${ZLIB_SRCDIR}/inffast.h
    ${ZLIB_SRCDIR}/inffixed.h
    ${ZLIB_SRCDIR}/inflate.h
    ${ZLIB_SRCDIR}/inftrees.h
    ${ZLIB_SRCDIR}/trees.h
    ${ZLIB_SRCDIR}/zutil.h
)
set(ZLIB_SOURCES
    ${ZLIB_SRCDIR}/adler32.c
    ${ZLIB_SRCDIR}/compress.c
    ${ZLIB_SRCDIR}/crc32.c
    ${ZLIB_SRCDIR}/deflate.c
    ${ZLIB_SRCDIR}/gzclose.c
    ${ZLIB_SRCDIR}/gzlib.c
    ${ZLIB_SRCDIR}/gzread.c
    ${ZLIB_SRCDIR}/gzwrite.c
    ${ZLIB_SRCDIR}/inflate.c
    ${ZLIB_SRCDIR}/infback.c
    ${ZLIB_SRCDIR}/inftrees.c
    ${ZLIB_SRCDIR}/inffast.c
    ${ZLIB_SRCDIR}/trees.c
    ${ZLIB_SRCDIR}/uncompr.c
    ${ZLIB_SRCDIR}/zutil.c
)

add_library("zlib" SHARED
        "${ZLIB_SOURCES}" "${ZLIB_PUBLIC_HDRS}" "${ZLIB_PRIVATE_HDRS}")
target_include_directories("zlib" PUBLIC .)
set_target_properties("zlib" PROPERTIES SOVERSION "1")
set_target_properties("zlib" PROPERTIES VERSION "${ZLIB_VERSION}")

add_library("zlibstatic" STATIC
        "${ZLIB_SOURCES}" "${ZLIB_PUBLIC_HDRS}" "${ZLIB_PRIVATE_HDRS}")
target_include_directories("zlibstatic" PUBLIC .)

set_target_properties("zlib" "zlibstatic" PROPERTIES OUTPUT_NAME "z"
                                                     C_CLANG_TIDY "")
