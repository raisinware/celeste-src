// config.h - handmade byacc config for Celeste Linux
/* config_h.in.  Generated automatically from configure.in by autoheader.  */

#include <stdnoreturn.h>

#ifndef _XOPEN_SOURCE
	#define _XOPEN_SOURCE 500
#endif
#ifndef __has_attribute
	#define __attribute__(x) 0
#endif

/* Define to noreturn-attribute for gcc */
#define GCC_NORETURN noreturn

#if __has_attribute(format)
	/* Define to 1 if the compiler supports gcc-like printf attribute. */
	#define GCC_PRINTF 1

	/* Define to printf-attribute for gcc */
	#define GCC_PRINTFLIKE(x,y) __attribute__((format(printf, x, y)))

	/* Define to 1 if the compiler supports gcc-like scanf attribute. */
	#define GCC_SCANF 1

	/* Define to sscanf-attribute for gcc */
	#define GCC_SCANFLIKE(x,y) __attribute__((format(scanf, x, y)))
#else
	#define GCC_PRINTF 0
	#define GCC_SCANF 0
#endif

#if __has_attribute(unused)
	/* Define to unused-attribute for gcc */
	#define GCC_UNUSED __attribute__((unused))
#endif

/* Define if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H

/* Define if you have the `getopt' function. */
#define HAVE_GETOPT

/* Define if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H

/* Define to 1 if getopt variables are declared in header */
#define HAVE_GETOPT_HEADER

/* Define if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H

/* Define if you have the `dbmalloc' library (-ldbmalloc). */
// #undef HAVE_LIBDBMALLOC

/* Define if you have the `dmalloc' library (-ldmalloc). */
// #undef HAVE_LIBDMALLOC

/* Define if you have the <memory.h> header file. */
// #undef HAVE_MEMORY_H

/* Define to 1 if mkstemp() is available and working. */
#define HAVE_MKSTEMP

/* Define if you have the <stdint.h> header file. */
#define HAVE_STDINT_H

/* Define if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H

/* Define if <stdnoreturn.h> header is available and working */
#define HAVE_STDNORETURN_H

/* Define if you have the <strings.h> header file. */
#define HAVE_STRINGS_H

/* Define if you have the <string.h> header file. */
#define HAVE_STRING_H

/* Define if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H

/* Define if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H

/* Define if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H

/* Define if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF

/* Define to maximum table size (default: 32500) */
#define MAXTABLE 32500

/* Define to 1 if filesystem supports mixed-case filenames. */
#define MIXEDCASE_FILENAMES

/* Define to 1 if we must include getopt.h */
// #undef NEED_GETOPT_H

/* Define to 1 if you want to perform memory-leak testing. */
// #undef NO_LEAKS

/* Define if you have the ANSI C header files. */
#define STDC_HEADERS

/* Define if C11 _Noreturn keyword is supported */
#define STDC_NORETURN

/* Define to the system name. */
#define SYSTEM_NAME "celeste0.1"

/* "Define to 1 if you want to use dbmalloc for testing." */
// #undef USE_DBMALLOC

/* "Define to 1 if you want to use dmalloc for testing." */
// #undef USE_DMALLOC

/* "Define to 1 if you want to use valgrind for testing." */
// #undef USE_VALGRIND

/* Define to 1 to enable backtracking extension */
#define YYBTYACC 1

/* Define to 1 if you want to perform memory-leak testing. */
// #undef YY_NO_LEAKS

/* Define to `int' if <sys/types.h> does not define. */
// #undef mode_t
