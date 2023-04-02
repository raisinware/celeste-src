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

#if defined(__STDC__) && (__STDC_VERSION__ < 201710L)
	// stop compilation if not compiling in C17+ mode.
	// most of the code could probably compile in C99/C11 with some
	// modifications, but that would require the use of more ugly compiler
	// extensions and you already need a C++17 compiler to compile LLVM.

	#error Please compile Celeste Linux in C17 mode or higher.
#endif


// Celeste code should always have access to assertions, noreturn, and bool
#include <assert.h>
#include <stdnoreturn.h>

#if defined(__STDC__) && (__STDC_VERSION__ < 202000L)
	// these should have been keywords from the start
	#include <stdbool.h>
#endif

// no-op attribute checking macros for pre-C2x and non-gcc compilers
#ifndef __has_c_attribute
	#define __has_c_attribute(x) 0
#endif
#ifndef __has_attribute
	#define __has_attribute(x) 0
#endif

// __deprecated attribute (C2x)
#if __has_c_attribute(deprecated)
	#define __deprecated(msg) [[deprecated(msg)]]
#elif __has_attribute(deprecated)
	#define __deprecated(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
	#define __deprecated(msg) __declspec(deprecated(msg))
#endif

// __EXPLICIT_FALLTHROUGH__ attribute (C2x)
#if __has_c_attribute(fallthrough)
	#define __EXPLICIT_FALLTHROUGH__ [[fallthrough]]
#elif __has_attribute(unused)
	#define __EXPLICIT_FALLTHROUGH__ __attribute__((fallthrough))
#else
	#define __EXPLICIT_FALLTHROUGH__
#endif

// __maybe_unused attribute (C2x)
#if __has_c_attribute(maybe_unused)
	#define __maybe_unused [[maybe_unused]]
#elif __has_attribute(unused)
	#define __maybe_unused __attribute__((unused))
#else
	#define __maybe_unused
#endif

// __nodiscard attribute (C2x)
#if __has_c_attribute(nodiscard)
	#define __nodiscard(msg) [[nodiscard(msg)]]
#elif __has_attribute(warn_unused_result)
	#define __nodiscard(msg) __attribute__((warn_unused_result(msg)))
#else
	#define __nodiscard(msg)
#endif

// use noreturn attribute on C2x instead of the C11/C17 version.
// very hacky but important for verifying code compatibility
#if defined(noreturn) && __has_c_attribute(noreturn)
	#undef noreturn
	#define noreturn [[__noreturn__]]
#endif

// __reproducible (C2x)
#if __has_c_attribute(reproducible)
	#define __reproducible [[reproducible]]
#elif __has_attribute(pure)
	#define __reproducible __attribute__((pure))
#endif

// __unsequenced (C2x)
#if __has_c_attribute(unsequenced)
	#define __unsequenced [[unsequenced]]
#elif __has_attribute(const)
	#define __unsequenced __attribute__((const))
#endif

// __used attribute (gnu extension)
#if __has_attribute(used)
	#define __used __attribute__((used))
#endif
