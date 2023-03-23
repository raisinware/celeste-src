// SPDX-License-Identifier: 0BSD
// version.h - autoconf package macros seperated out for code clarity

/*
Copyright (C) 2023 raisinware

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
*/

#pragma once

// short name
#define PACKAGE "gmake"

// version
#define VERSION "4.4.1"

// why is there a 2nd version macro gnu wtf
#define PACKAGE_VERSION VERSION

// long name
#define PACKAGE_NAME "Celeste Gmake"

// long name + version
#define PACKAGE_STRING "Celeste Gmake 4.4.1"

// project url
#define PACKAGE_URL "https://github.com/raisinware/celeste-src/"

// bug report url
#define PACKAGE_BUGREPORT "https://github.com/raisinware/celeste-src/issues"

// tarball name
// TODO: check if this is even needed
#define PACKAGE_TARNAME "gmake"

// lib dir location
#define LIBDIR "/usr/lib"

// locale dir location
#define LOCALEDIR "/usr/share/locale"

// system host
#define MAKE_HOST "celeste0.1"
