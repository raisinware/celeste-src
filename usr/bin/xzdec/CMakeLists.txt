# SPDX-License-Identifier: Apache-2.0 OR MIT

set(XZDEC_SRCDIR "${CMAKE_SOURCE_DIR}/extern/publicdomain/xz-utils/src")

set(XZDEC_SOURCES
    config.h
    ${XZDEC_SRCDIR}/common/sysdefs.h
    ${XZDEC_SRCDIR}/common/tuklib_common.h
    ${XZDEC_SRCDIR}/common/tuklib_config.h
    ${XZDEC_SRCDIR}/common/tuklib_exit.c
    ${XZDEC_SRCDIR}/common/tuklib_exit.h
    ${XZDEC_SRCDIR}/common/tuklib_gettext.h
    ${XZDEC_SRCDIR}/common/tuklib_progname.c
    ${XZDEC_SRCDIR}/common/tuklib_progname.h
    ${XZDEC_SRCDIR}/xzdec/xzdec.c
)

add_executable("xzdec" ${XZDEC_SOURCES})

set_target_properties("xzdec" PROPERTIES C_CLANG_TIDY "")
target_link_libraries("xzdec" PRIVATE liblzma)
target_compile_definitions("xzdec" PRIVATE HAVE_CONFIG_H)
target_include_directories("xzdec" PRIVATE
    ${XZDEC_SRCDIR}/common
    ${XZDEC_SRCDIR}/liblzma/api
    .
)

