# SPDX-License-Identifier: Apache-2.0 OR ISC

cmake_minimum_required(VERSION "3.20")
project("Celeste Linux Core Userspace" VERSION "0.1")
set(CMAKE_C_STANDARD "23")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
add_compile_options(-Wall -Wextra -Wpedantic)
add_compile_options(-Werror=implicit-function-declaration -Werror=implicit-int)

# includes
include(CheckSymbolExists)
include(ClangFormat)

# options
option(CELESTE_CLANG_TIDY "Enable clang tidy while building." OFF)

# silence dumb musl-clang warnings 
if(${CMAKE_C_COMPILER} MATCHES "musl-clang")
    add_compile_options(-Wno-unused-command-line-argument)
    add_link_options(-Wno-unused-command-line-argument)
endif()

# generate gitignore when building out of tree
if(NOT PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    file(GENERATE OUTPUT .gitignore CONTENT "*")
endif()

# check if compiling for glibc
check_symbol_exists(__GLIBC__ "features.h" GLIBC_TARGET)
if(GLIBC_TARGET)
    message(WARNING "Compiling the userspace on a glibc target is only "
                    "supported for development testing purposes.")
endif()

# handle options
if(CELESTE_CLANG_TIDY)
    set(CMAKE_C_CLANG_TIDY clang-tidy --config=${PROJECT_SOURCE_DIR}/.clang-tidy)
endif()

# start rest of build process
add_subdirectory(contrib)
add_subdirectory(usr)
