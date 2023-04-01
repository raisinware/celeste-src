# SPDX-License-Identifier: Apache-2.0 OR ISC

add_executable("printf" printf.c)

set_target_properties("printf" PROPERTIES C_CLANG_TIDY "")
target_link_libraries("printf" libutil)
