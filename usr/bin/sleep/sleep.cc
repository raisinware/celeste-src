/* SPDX-License-Identifier: Apache-2.0 OR ISC */

/* sleep.cc - sleep for x amount of seconds
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

#include <iostream>
#include <string>
#include <unistd.h>

int main(int argc, const char *argv[]) {
	try {
		// make sure an argument was passed
		if (argv[1] != nullptr) {
			std::string arg = argv[1];
			std::size_t pos = 0;

			const int seconds = std::stoi(arg, &pos);

			// throw an exception if more then 1 argument was given,
			// or if theres any stray characters in the argument
			if ( argc != 2 || pos < arg.size() ) {
				throw 1;
			}

			sleep(seconds);
		}

		// throw exception if no argument was passed
		else {
			throw 1;
		}
	}

	catch (...) {
		std::cout << "usage: sleep [seconds]" << std::endl;
		return 1;
	}

	return 0;
}
