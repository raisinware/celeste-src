/* SPDX-License-Identifier: Apache-2.0 OR ISC */
/* nproc.c - get the available cpus */

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/** Returns available cores/CPUs. */
int getCPUs() {
# if defined(__linux__)
	/* use 'sched_getaffinity' syscall wrapper on linux */
	cpu_set_t set;

	if (sched_getaffinity(0, sizeof(cpu_set_t), &set) == 0)
	{
		int cpus = CPU_COUNT(&set);
		return cpus;
	}

# elif defined(_SC_NPROCESSORS_ONLN)
	/* fallback to sysconf on supported systems for getting online cpus */
	int cpus = sysconf(_SC_NPROCESSORS_ONLN)

	if (cpus > 0) {
		return cpus;
	}
# endif

	return 1;
}


/** Returns all cores/CPUs. */
int getAllCPUs() {
	int cpus = getCPUs();

	/* TODO: make this work properly on musl */
# ifdef _SC_NPROCESSORS_CONF
	/* use sysconf to determine all avalible cpus on supported systems */
	int all_cpus = sysconf(_SC_NPROCESSORS_CONF);
	if (all_cpus >= cpus) {
		return all_cpus;
	}
# endif

	return cpus;
}

int main(int argc, const char *argv[]) {
	/* check for --all argument and call getAllCPUs() */
	if (argc == 2 && (strcmp(argv[1], "--all") == 0)) {
		printf("%d\n", getAllCPUs());
		return 0;
	}

	printf("%d\n", getCPUs());
}
