// SPDX-License-Identifier: Apache-2.0 OR MIT
// CelesteUtil.h - main header file for libutil

// libutil is a unportable, Celeste specific library for common utility
// functions shared between commands. Most of the functions here are
// implementations of some BSD libc functions, to allow for easy porting of BSD
// programs to Celeste Linux, and also because the interfaces are nicely
// designed.
// -------------------------------------------------------------------------
// !!!!!! THIS LIBRARY IS UNPORTABLE, AND HAS NO API/ABI GUARANTEES. !!!!!!!
// -------------------------------------------------------------------------

#pragma once
#include "../../include/CelesteC.h"
#include <string.h>

/// no-op macro for bsd compat
#define setprogname(x)                                                         \
	do {                                                                       \
	} while (0)

/// Determine if 2 strings are equal. Returns true if equal, and false if not.
#define STREQ(str1, str2) (strcmp(str1, str2) == 0)

/// Get the name of the current program
[[CELESTE_PUBLIC, __reproducible__]]
const char* getprogname(void);

/// Convert a string into a number with error checking
[[CELESTE_PUBLIC, CELESTE_NONNULL(1)]]
long long strtonum(const char* str, long long minval, long long maxval,
                   const char** errstrp);
