# SPDX-License-Identifier: Apache-2.0 OR ISC

add_executable("sleep" sleep.c)

target_link_libraries("sleep" util)
