// SPDX-License-Identifier: 0BSD
// CelesteC.h - internal convience header for base Celeste Linux code.
// mostly pulls in headers that should have been keywords in C.

// Copyright (C) 2023 raisinware
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
// OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
// CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

// if your compiler doesn't support this extension, it sucks
#pragma once

#if defined(__STDC__) && (__STDC_VERSION__ < 201112L)
	// stop compilation if not compiling in C11+ mode.
	// most of the code could probably compile in C99 with some modifications,
	// but that would require the use of ugly compiler extensions and C11 has
	// been out for a decade already. If your compiler can't do C11, then it
	// can't even compile the kernel anyways.

	#error Please compile Celeste Linux in C11 mode or higher.
#endif

// Celeste code should always have access to assertions
#include <assert.h>

#if defined(__STDC__) && (__STDC_VERSION__ < 202000L)
	// these should have been keywords from the start
	#include <stdbool.h>
	#include <stdnoreturn.h>
#endif

// compat macros for pre-C2x and non-gcc compilers
#ifndef __has_attribute
	#define __has_attribute(x) 0
#endif
#ifndef __has_c_attribute
	#define __has_c_attribute(x) 0
#endif

// __deprecated attribute
#if __has_c_attribute(deprecated)
	#define __deprecated(msg) [[deprecated(msg)]]
#elif __has_attribute(deprecated)
	#define __deprecated(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
	#define __deprecated(msg) __declspec(deprecated(msg))
#endif

// __fallthrough attribute
#if __has_c_attribute(fallthrough)
	#define __fallthrough [[fallthrough]]
#elif __has_attribute(unused)
	#define __fallthrough __attribute__((fallthrough))
#else
	#define __fallthrough
#endif

// __maybe_unused attribute
#if __has_c_attribute(maybe_unused)
	#define __maybe_unused [[maybe_unused]]
#elif __has_attribute(unused)
	#define __maybe_unused __attribute__((unused))
#else
	#define __maybe_unused
#endif

// __nodiscard attribute
#if __has_c_attribute(nodiscard)
	#define __nodiscard [[nodiscard]]
#elif __has_attribute(warn_unused_result)
	#define __nodiscard __attribute__((warn_unused_result))
#else
	#define __nodiscard
#endif
