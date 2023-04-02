# SPDX-License-Identifier: Apache-2.0 OR MIT

add_executable("cat" cat.c)

target_link_libraries("cat" libutil)
target_clangformat_setup("cat")
