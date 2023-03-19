// SPDX-License-Identifier: Apache-2.0 OR ISC
// strtonum.c - convert string to number with strict error checking

#include "CelesteUtil.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

long long strtonum(const char* str, long long minval, long long maxval,
                   const char** errstrp) {
	long long num = 0;
	char* leftover;

	// save and reset errno to 0 incase something else set it
	int saved_errno = errno;
	errno = 0;

	// validate inputs
	if (minval > maxval){
		errno = EINVAL;
	} else {
		num = strtoll(str, &leftover, 10);

		if ( (num < minval) || (num > maxval) )
			errno = ERANGE;
		if ( (str == leftover) || (*leftover != '\0') )
			errno = EINVAL;
	}

	// if error happened, set errstrp to an error message, else restore errno
	if (errno != 0){
		if (errstrp != NULL)
			*errstrp = strerror(errno);

		num = 0;
	} else {
		errno = saved_errno;
	}
	
	return num;
}
