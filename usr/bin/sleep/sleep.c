// SPDX-License-Identifier: Apache-2.0 OR MIT
// sleep.c - sleep for x amount of seconds

#include "../../include/CelesteC.h"
#include "../../lib/util/CelesteUtil.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/// Display usage message and exit with an error
noreturn static void usage(void) {
	fprintf(stderr, "usage: %s [seconds]\n", getprogname());
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	const char* errstr;

	// check that only 1 argument was passed
	if (argc != 2)
		usage();

	unsigned int num = strtonum(argv[1], 0, UINT_MAX, &errstr);

	if (errstr != NULL) {
		fprintf(stderr, "Error: %s\n", errstr);
		usage();
	} else {
		sleep(num);
	}

	return EXIT_SUCCESS;
}
