#pragma once

#define _ALL_SOURCE

#ifndef __has_include
	#define __has_include(x) 0
#endif
#ifndef __has_attribute
	#define __has_attribute(x) 0
#endif

#define PACKAGE_NAME      "xz"
#define PACKAGE           PACKAGE_NAME
#define PACKAGE_BUGREPORT "xz@tukaani.org"
#define PACKAGE_URL       "https://tukaani.org/xz/"
#define LOCALEDIR         "/usr/share/locale"

#define TUKLIB_SYMBOL_PREFIX lzma_
#define ASSUME_RAM 128
#define ENABLE_NLS 1

#define HAVE_CHECK_CRC        1
#define HAVE_CHECK_CRC64      1
#define HAVE_CHECK_SHA256     1
#define HAVE_DECODERS         1
#define HAVE_DECODER_ARM      1
#define HAVE_DECODER_ARMTHUMB 1
#define HAVE_DECODER_ARM64    1
#define HAVE_DECODER_DELTA    1
#define HAVE_DECODER_IA64     1
#define HAVE_DECODER_LZMA1    1
#define HAVE_DECODER_LZMA2    1
#define HAVE_DECODER_POWERPC  1
#define HAVE_DECODER_SPARC    1
#define HAVE_DECODER_X86      1
#define HAVE_ENCODERS         1
#define HAVE_ENCODER_ARM      1
#define HAVE_ENCODER_ARMTHUMB 1
#define HAVE_ENCODER_ARM64    1
#define HAVE_ENCODER_DELTA    1
#define HAVE_ENCODER_IA64     1
#define HAVE_ENCODER_LZMA1    1
#define HAVE_ENCODER_LZMA2    1
#define HAVE_ENCODER_POWERPC  1
#define HAVE_ENCODER_SPARC    1
#define HAVE_ENCODER_X86      1
#define HAVE_MF_BT2           1
#define HAVE_MF_BT3           1
#define HAVE_MF_BT4           1
#define HAVE_MF_HC3           1
#define HAVE_MF_HC4           1
#define HAVE_LZIP_DECODER     1

#define HAVE_STDBOOL_H  1
#define HAVE__BOOL      1
#define HAVE_STDINT_H   1
#define HAVE_INTTYPES_H 1
#define HAVE_STDLIB_H   1
#define HAVE_STDIO_H    1
#define HAVE_STRINGS_H  1
#define HAVE_STRING_H   1
#define HAVE_DCGETTEXT  1
#define HAVE_GETTEXT    1
#define HAVE_ICONV      1
#define HAVE_UNISTD_H   1
#define HAVE_FCNTL_H    1
#define HAVE_GETOPT_H   1
#define HAVE_LIMITS_H   1
#define HAVE_FUTIMENS   1
#define HAVE_FUTIMES    1
#define HAVE_FUTIMESAT  1
#define HAVE_OPTRESET   1

#define SIZEOF_SIZE_T sizeof(size_t)

#ifdef __nodebug__
	#define NDEBUG 1
#endif

#ifdef __GNUC__
	#define HAVE___BUILTIN_BSWAPXX         1
	#define HAVE___BUILTIN_ASSUME_ALIGNEDx 1
#else
	#define HAVE_BYTESWAP_H 1
	#define HAVE_BSWAP_16   1
	#define HAVE_BSWAP_32   1
	#define HAVE_BSWAP_64   1
#endif

#if defined(__x86_64__) //|| defined(__aarch64__)
	#define TUKLIB_FAST_UNALIGNED_ACCESS 1
#endif

#define HAVE_CLOCK_GETTIME   1
#define HAVE_CLOCK_MONOTONIC 1

#define MYTHREAD_POSIX                 1
#define HAVE_PTHREAD_CONDATTR_SETCLOCK 1
#define HAVE_POSIX_FADVISE             1
#define HAVE_PTHREAD_PRIO_INHERIT      1

#define TUKLIB_CPUCORES_SCHED_GETAFFINITY 1
#define TUKLIB_PHYSMEM_SYSCONF            1

#if __has_attribute(__constructor__)
	#define HAVE_FUNC_ATTRIBUTE_CONSTRUCTOR 1
#endif

#ifdef __x86_64__
	#if __has_include("cpuid.h")
		#define HAVE_CPUID_H 1
	#endif
	#if __has_include("immintrin.h")
		#define HAVE_IMMINTRIN_H       1
		#define HAVE__MM_MOVEMASK_EPI8 1
		#ifdef __PCLMUL__
			#define HAVE_USABLE_CLMUL  1
		#endif
	#endif
#endif

#define HAVE_GETOPT_LONG             1
#define HAVE_PROGRAM_INVOCATION_NAME 1
#define HAVE_MBRTOWC                 1
#define HAVE_WCWIDTH                 1
#define HAVE_SYMBOL_VERSIONS_LINUX   1
