# SPDX-License-Identifier: Apache-2.0 OR MIT

add_executable("expr" expr.c)

set_target_properties("expr" PROPERTIES C_CLANG_TIDY "")
target_link_libraries("expr" libutil)
