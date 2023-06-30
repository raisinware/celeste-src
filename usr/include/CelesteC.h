// SPDX-License-Identifier: 0BSD
// CelesteC.h - internal convience header for base Celeste Linux code.
// mostly C2x attributes

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

/// Stop compilation if not compiling in C2x+ mode.
/// Most of the code could probably compile in C99/C11/C17 with some
/// modifications (replacing C2x attributes with gnu ones + accompanying
/// portability cruft, replacing `nullptr` with `NULL`, etc...), but i'd
/// rather focus on keeping cruft low for the eventual 1.0 release.
#if defined(__STDC__) && (__STDC_VERSION__ < 202000L)
	#error Please compile Celeste Linux in C2x mode or higher.
#endif

[[maybe_unused]] extern bool __celeste_isoc_compliance; // NOLINT

/// `__reproducible__` and `__unsequenced__` attributes
///
/// Portability cruft for gcc/clang. All of these will be removed once clang
/// supports these attributes in a release version, along with uses of the
/// underscored variants being replaced with their non-underscored versions.
///
/// TODO: remove once clang supports these attributes in a release version
#if !__has_c_attribute(reproducible) && __has_c_attribute(gnu::pure)
	#define __reproducible__ gnu::pure /* NOLINT */
#endif
#if !__has_c_attribute(unsequenced) && __has_c_attribute(gnu::const)
	#define __unsequenced__ gnu::const /* NOLINT */
#endif

/// `CELESTE_NONNULL` attribute
///
/// stuff
#if __has_c_attribute(gnu::nonnull)
	#define CELESTE_NONNULL(...) gnu::nonnull(__VA_ARGS__)
#else
	#define CELESTE_NONNULL(...)
#endif

/// `CELESTE_PUBLIC` and `CELESTE_PRIVATE` attributes
///
/// Controls whether a symbol is emitted in the exported symbol table on a gcc
/// compatible compiler.
#if __has_c_attribute(gnu::visibility)
	#define CELESTE_PUBLIC gnu::visibility("default")
	#define CELESTE_PRIVATE gnu::visibility("hidden")
#else
	#define CELESTE_PUBLIC
	#define CELESTE_PRIVATE
#endif

/// `CELESTE_USED` attribute
///
/// On gcc compatible compilers, this macro is set to the `gnu::used` attribute,
/// which makes it so the variable/function is emitted even when the
/// variable/function appears to be unused.
///
/// On an ISO C compatible compiler, this is set to the `maybe_unused`
/// attribute, which silences the warning that the variable/function is unused.
#if __has_c_attribute(gnu::used)
	#define CELESTE_USED gnu::used
#else
	#define CELESTE_USED maybe_unused
#endif
