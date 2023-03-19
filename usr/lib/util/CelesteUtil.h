// SPDX-License-Identifier: Apache-2.0 OR ISC
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

/// Get the name of the current program
const char* getprogname(void);

/// no-op macro for bsd compat
#define setprogname(x)

/// Convert a string into a number with error checking
long long strtonum(const char* str, long long minval, long long maxval,
                   const char** errstrp);
