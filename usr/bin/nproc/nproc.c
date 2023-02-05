/* SPDX-License-Identifier: Apache-2.0 OR ISC */

/* nproc.c - get the available cpus
 *
 * Copyright (c) 2023 by raisinware
 * 
 * Licensed under either the Apache-2.0 or ISC Licenses, at your option.
 * You may obtain a copy of each license at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *     https://github.com/raisinware/celeste-src/blob/main/LICENSE.ISC
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>

int getcpus() {
	/* use 'sched_getaffinity' syscall wrapper on linux */
	cpu_set_t set;
	if (sched_getaffinity(0, sizeof(cpu_set_t), &set) == 0)
	{
		int cpus = CPU_COUNT(&set);
		return cpus;
	}
	return 1;
}

int main() {
	printf("%d\n", getcpus());
}
