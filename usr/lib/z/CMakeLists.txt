# SPDX-License-Identifier: Apache-2.0 OR ISC

set(ZLIB_FULL_VERSION "1.2.13")

set(ZLIB_PUBLIC_HDRS
    ../../../contrib/zlib/zconf.h
    ../../../contrib/zlib/zlib.h
)
set(ZLIB_PRIVATE_HDRS
    ../../../contrib/zlib/crc32.h
    ../../../contrib/zlib/deflate.h
    ../../../contrib/zlib/gzguts.h
    ../../../contrib/zlib/inffast.h
    ../../../contrib/zlib/inffixed.h
    ../../../contrib/zlib/inflate.h
    ../../../contrib/zlib/inftrees.h
    ../../../contrib/zlib/trees.h
    ../../../contrib/zlib/zutil.h
)
set(ZLIB_SOURCES
    ../../../contrib/zlib/adler32.c
    ../../../contrib/zlib/compress.c
    ../../../contrib/zlib/crc32.c
    ../../../contrib/zlib/deflate.c
    ../../../contrib/zlib/gzclose.c
    ../../../contrib/zlib/gzlib.c
    ../../../contrib/zlib/gzread.c
    ../../../contrib/zlib/gzwrite.c
    ../../../contrib/zlib/inflate.c
    ../../../contrib/zlib/infback.c
    ../../../contrib/zlib/inftrees.c
    ../../../contrib/zlib/inffast.c
    ../../../contrib/zlib/trees.c
    ../../../contrib/zlib/uncompr.c
    ../../../contrib/zlib/zutil.c
)

add_library("zlib" SHARED
        "${ZLIB_SOURCES}" "${ZLIB_PUBLIC_HDRS}" "${ZLIB_PRIVATE_HDRS}")
add_library("zlibstatic" STATIC
        "${ZLIB_SOURCES}" "${ZLIB_PUBLIC_HDRS}" "${ZLIB_PRIVATE_HDRS}")

set_target_properties("zlib" PROPERTIES SOVERSION "1")
set_target_properties("zlib" PROPERTIES VERSION "${ZLIB_FULL_VERSION}")

set_target_properties("zlib" "zlibstatic" PROPERTIES OUTPUT_NAME "z")
