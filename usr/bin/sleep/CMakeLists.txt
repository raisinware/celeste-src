# SPDX-License-Identifier: Apache-2.0 OR MIT

add_executable("sleep" sleep.c)

target_link_libraries("sleep" libutil)
target_clangformat_setup("sleep")
