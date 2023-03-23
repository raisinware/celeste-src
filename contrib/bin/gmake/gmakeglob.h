// SPDX-License-Identifier: MIT
// gmakeglob.h - header for musl glob functions with gnu extensions
/*
----------------------------------------------------------------------
Copyright © 2005-2020 Rich Felker, et al.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
----------------------------------------------------------------------
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <sys/stat.h>

typedef struct {
	size_t gl_pathc;
	char **gl_pathv;
	size_t gl_offs;
	int __dummy1;
	void *__dummy2[5];
} gmake_glob_t;

int  gmake_glob(const char *__restrict, int, int (*)(const char *, int), gmake_glob_t *__restrict);
void gmake_globfree(gmake_glob_t *);

#define GMAKE_GLOB_ERR      0x01
#define GMAKE_GLOB_MARK     0x02
#define GMAKE_GLOB_NOSORT   0x04
#define GMAKE_GLOB_DOOFFS   0x08
#define GMAKE_GLOB_NOCHECK  0x10
#define GMAKE_GLOB_APPEND   0x20
#define GMAKE_GLOB_NOESCAPE 0x40
#define GMAKE_GLOB_PERIOD   0x80

#define GMAKE_GLOB_TILDE       0x1000
#define GMAKE_GLOB_TILDE_CHECK 0x4000

#define GMAKE_GLOB_NOSPACE 1
#define GMAKE_GLOB_ABORTED 2
#define GMAKE_GLOB_NOMATCH 3
#define GMAKE_GLOB_NOSYS   4

#ifdef __cplusplus
}
#endif
