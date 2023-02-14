/* SPDX-License-Identifier: Apache-2.0 OR ISC */

/* echo.cc - print all arguments and end with a newline
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

int main(int argc, const char *argv[]) {
    // iterate through most arguments and print, seperating each with a space.
	for ( int i=1; i < (argc - 1); i++ )
		std::cout << argv[i] << " ";
    
    // print the last argument
    if (argc > 1)
        std::cout << argv[argc - 1];

	std::cout << std::endl;

    return 0;
}
