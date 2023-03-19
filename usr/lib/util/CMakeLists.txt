# SPDX-License-Identifier: Apache-2.0 OR ISC

set(LIBUTIL_SOURCES
    progname.c 
)

add_library(util STATIC "${LIBUTIL_SOURCES}")
