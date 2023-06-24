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

#if defined(__STDC__) && (__STDC_VERSION__ < 202000L)
	// stop compilation if not compiling in C2x+ mode.
	// most of the code could probably compile in C99/C11/C17 with some
	// modifications, but i'd rather focus on keeping cruft low for the eventual
	// 1.0 release of Celeste Linux.

	#error Please compile Celeste Linux in C2x mode or higher.
#endif

// __reproducible (C2x)
#if __has_c_attribute(reproducible)
	#define __reproducible [[reproducible]]
#elif __has_c_attribute(gnu::pure)
	#define __reproducible [[gnu::pure]]
#else
	#define __reproducible
#endif

// __unsequenced (C2x )
#if __has_c_attribute(unsequenced)
	#define __unsequenced [[unsequenced]]
#elif __has_c_attribute(gnu::const)
	#define __unsequenced [[gnu::const]]
#else
	#define __unsequenced
#endif

// __used attribute (gnu extension)
#if __has_c_attribute(gnu::used)
	#define __used [[gnu::used]]
#else
	#define __used
#endif

#if __has_c_attribute(gnu::visibility)
	#define CELESTE_PUBLIC [[gnu::visibility("default")]]
	#define CELESTE_PRIVATE [[gnu::visibility("hidden")]]
#else
	#define CELESTE_PUBLIC
	#define CELESTE_PRIVATE
#endif

[[maybe_unused]]
extern bool __celeste_isoc_compliance; // NOLINT
