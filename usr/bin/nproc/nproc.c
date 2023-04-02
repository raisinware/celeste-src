// SPDX-License-Identifier: Apache-2.0 OR MIT
// nproc.c - get the available cpus

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STREQ(str1, str2) (strcmp(str1, str2) == 0)

/// Returns available cores/CPUs.
int getCPUs(void) {
#if defined(__linux__)
	// use 'sched_getaffinity' syscall wrapper on linux
	cpu_set_t set;

	if (sched_getaffinity(0, sizeof(cpu_set_t), &set) == 0) {
		int cpus = CPU_COUNT(&set);
		return cpus;
	}

#elif defined(_SC_NPROCESSORS_ONLN)
	// fallback to sysconf on supported systems for getting online cpus
	int cpus = sysconf(_SC_NPROCESSORS_ONLN);

	if (cpus > 0)
		return cpus;
#endif

	return 1;
}

/// Returns all cores/CPUs.
int getAllCPUs(void) {
	int cpus = getCPUs();

	/// TODO: make this work properly on musl
#ifdef _SC_NPROCESSORS_CONF
	// use sysconf to determine all avalible cpus on supported systems
	int all_cpus = sysconf(_SC_NPROCESSORS_CONF);
	if (all_cpus >= cpus) {
		return all_cpus;
	}
#endif

	return cpus;
}

int main(int argc, char* argv[]) {
	// check for --all argument and call getAllCPUs()
	if (argc == 2 && STREQ(argv[1], "--all")) {
		printf("%d\n", getAllCPUs());
		return 0;
	}

	printf("%d\n", getCPUs());
	return 0;
}
