# SPDX-License-Identifier: Apache-2.0 OR ISC

cmake_minimum_required(VERSION "3.20")
project("Celeste Linux Core Userspace" VERSION "0.1")
set(CMAKE_C_STANDARD "23")
add_compile_options(-Wall -Wextra -Wpedantic)
add_compile_options(-Werror=implicit-function-declaration -Werror=implicit-int)

# includes
include(CheckSymbolExists)

# check if compiling for glibc
check_symbol_exists(__GLIBC__ "features.h" GLIBC_TARGET)
if(GLIBC_TARGET)
    message(WARNING "Compiling the userspace on a glibc target is only "
                    "supported for development testing purposes.")
endif()

# start rest of build process
add_subdirectory(contrib)
add_subdirectory(usr)
