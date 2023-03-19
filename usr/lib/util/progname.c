
#define _GNU_SOURCE
#include "CelesteUtil.h"
#include <errno.h>

const char* getprogname(void){
    return program_invocation_short_name;
}
