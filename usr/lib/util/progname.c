// SPDX-License-Identifier: Apache-2.0 OR ISC
// progname.c - get the current program name

#define _GNU_SOURCE
#include "CelesteUtil.h"
#include <errno.h>

const char* getprogname(void){
    return program_invocation_short_name;
}
