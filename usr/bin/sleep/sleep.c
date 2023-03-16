/* SPDX-License-Identifier: Apache-2.0 OR ISC */
/* sleep.c - sleep for x amount of seconds */

#define _GNU_SOURCE
#include "../../include/CelesteC.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/** Display usage message and exit with an error */
static noreturn void usage(void){
	fprintf(stderr, "usage: %s [seconds]\n",
		program_invocation_short_name);
	exit(EXIT_FAILURE);
}

/** Convert a string into an unsigned int with strict error checking */
unsigned int getuint(const char* str){
	/* reset errno to 0 incase something else set it */
	errno = 0;

	char* leftover = NULL;
	unsigned long secs = strtoul(str, &leftover, 10);

	/* check that a valid number was fed with no trailing characters */
	if ( (errno == 0 && str && !*leftover) && (str != leftover) && (secs <= UINT_MAX) )
		return secs;
	else usage();
}

int main(int argc, char* argv[]){
	/* check that only 1 argument was passed */
	if ( argc != 2 ) 
		usage();

	sleep(getuint(argv[1]));

	return EXIT_SUCCESS;
}
