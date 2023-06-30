// SPDX-License-Identifier: Apache-2.0 OR MIT
// cat.c - concatnate files nya~ :333 ^w^

#define _POSIX_C_SOURCE 200809L
#include "../../include/CelesteC.h"
#include "../../lib/util/CelesteUtil.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUF_SIZE 4096

const char nya[] = "\nnya~ :333 (^w^)";

/// Print error message, usage of command, and exit program with failure
[[noreturn]]
static void usage(void) {
	if (errno != 0) {
		perror("Error");
	}

	puts(nya);
	fprintf(stderr, "Usage ^w^: %s [-u] [files]\n", getprogname());
	exit(EXIT_FAILURE);
}

/// Print a file to stdout. Uses the sendfile linux syscall for maximum
/// performance. Returns 0 on success, and -1 on failure.
[[nodiscard("Failures should be handled")]]
static int print_file(int _fd) {
	struct stat finfo;
	size_t rbytes;
	ssize_t sfrc;

	int _rc = fstat(_fd, &finfo);

	// error check
	if (_rc != 0) {
		return -1;
	}

	rbytes = finfo.st_size;

	while (rbytes != 0) {
		sfrc = sendfile(STDOUT_FILENO, _fd, nullptr, rbytes);

		// error check
		if (sfrc == -1) {
			return -1;
		}

		rbytes -= sfrc;
	}

	return 0;
}

/// write `len` amount of bytes to `buf`, and return the bytes written
static ssize_t writeall(int _fd, void* buf, size_t len) {
	ssize_t count = 0;

	while (count < len) {
		ssize_t _wb = write(_fd, count + (char*)buf, len - count);
		if (_wb < 1) {
			return _wb;
		}
		count += _wb;
	}

	return count;
}

/// Print stdin to stdout.
/// TODO: use dynamic memory allocation instead of a char[] buffer
static void print_stdin(void) {
	ssize_t len;
	ssize_t _bw;

	char buffer[BUF_SIZE];
	int _fd = STDIN_FILENO;
	size_t size = sizeof(buffer);

	for (;;) {
		len = read(_fd, buffer, size);

		if (len < 0) {
			perror("Error");
			exit(EXIT_FAILURE);
		}

		if (len < 1) {
			break;
		}

		_bw = writeall(STDOUT_FILENO, buffer, len);

		if (len != _bw) {
			fputs("Error: couldn't write buffer to stdout\n", stderr);
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char* argv[]) {
	int retcode;

	for (;;) {
		switch (getopt(argc, argv, "u")) {
		case 'u': // no-op for POSIX compat
			continue;
		default: // unknown option
			usage();
		case -1: // done parsing
			break;
		}
		break;
	}

	argc -= optind;
	argv += optind;

	if (argc < 1) {
		print_stdin();
		return 0;
	}

	// iterate through arguments
	for (int i = 0; i < argc; i++) {
		if (STREQ(argv[i], "-")) {
			print_stdin();
		} else {
			int _fd = open(argv[i], O_RDONLY);

			// quick error checking before calling print_file
			if ((_fd == -1) || (errno != 0)) {
				usage();
			}

			retcode = print_file(_fd);

			// check return code
			if (retcode != 0) {
				usage();
			}

			close(_fd);
		}
	}

	return 0;
}
