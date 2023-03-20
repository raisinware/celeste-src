# SPDX-License-Identifier: Apache-2.0 OR ISC

add_executable("expr" expr.c)

target_link_libraries("expr" libutil)
