/* SPDX-License-Identifier: Apache-2.0 OR ISC */

/* celeste-compat.h - minor portability cruft and misc macros.
 * yeah this file is ugly >~< */

/* if your compiler doesn't support this extension, it sucks */
#pragma once 

#if defined(__STDC__) && (__STDC_VERSION__ < 201112L)
    /* warn/error if not compiling in C11+ mode */
#   warning Please compile Celeste Linux in C11 standards mode or higher.
#endif

/* define feature macros to make testing on glibc less dumb */
#ifndef _GNU_SOURCE
#   define _GNU_SOURCE
#endif
#ifndef _BSD_SOURCE
#   define _BSD_SOURCE
#endif

/* this should be a keyword, not a header */
#include <assert.h>

#if (__STDC_VERSION__ > 201710L)
    /* define macros for C2x+ */
#   define noreturn [[__noreturn__]]
#else
    /* include headers for features that should just be keywords */
#   include <stdbool.h>
#   include <stdnoreturn.h>
#endif

#if defined(__GNUC__)
    /* gcc compatible compiler macros */    
#   if (__STDC_VERSION__ > 201710L)
        /* use C2x attribute syntax */
#       define __CELESTEID(str) [[gnu::used, gnu::section(".ident")]] \
            static const char* __CELESTEID = str
#   else
        /* old ugly attribute syntax */
#       define __CELESTEID(str) __attribute__((used)) \
            __attribute__((section(".ident"))) \
            static const char* __CELESTEID = str
#   endif
#else
    /* no-op macros for non-gcc compatible compilers */
#   define __CELESTEID(str)
#endif
