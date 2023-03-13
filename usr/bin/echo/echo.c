/* SPDX-License-Identifier: Apache-2.0 OR ISC */
/* echo.c - print all arguments and end with a newline */

#include <stdio.h>

int main(int argc, char *argv[]) {
	// iterate through most arguments and print to stdout.
	for ( int i=1; i < argc; i++ ) {
		fputs(argv[i], stdout);

		// print space if not the last argument
		if (i < (argc-1))
			fputc(' ', stdout);
	}

	// print newline
	puts("");

	return 0;
}
