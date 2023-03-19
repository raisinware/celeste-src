# SPDX-License-Identifier: Apache-2.0 OR ISC

set(LIBUTIL_SOURCES
    CelesteUtil.h
    progname.c 
    strtonum.c
)

add_library("libutil" STATIC "${LIBUTIL_SOURCES}")
set_target_properties("libutil" PROPERTIES OUTPUT_NAME "util")
