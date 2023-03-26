# SPDX-License-Identifier: Apache-2.0 OR ISC

set(XZ_SRCDIR "${CMAKE_SOURCE_DIR}/extern/publicdomain/xz-utils/src")

set(XZ_SOURCES
    config.h
    ${XZ_SRCDIR}/common/mythread.h
    ${XZ_SRCDIR}/common/sysdefs.h
    ${XZ_SRCDIR}/common/tuklib_common.h
    ${XZ_SRCDIR}/common/tuklib_config.h
    ${XZ_SRCDIR}/common/tuklib_exit.c
    ${XZ_SRCDIR}/common/tuklib_exit.h
    ${XZ_SRCDIR}/common/tuklib_gettext.h
    ${XZ_SRCDIR}/common/tuklib_integer.h
    ${XZ_SRCDIR}/common/tuklib_mbstr.h
    ${XZ_SRCDIR}/common/tuklib_mbstr_fw.c
    ${XZ_SRCDIR}/common/tuklib_mbstr_width.c
    ${XZ_SRCDIR}/common/tuklib_open_stdxxx.c
    ${XZ_SRCDIR}/common/tuklib_open_stdxxx.h
    ${XZ_SRCDIR}/common/tuklib_progname.c
    ${XZ_SRCDIR}/common/tuklib_progname.h
    ${XZ_SRCDIR}/xz/args.c
    ${XZ_SRCDIR}/xz/args.h
    ${XZ_SRCDIR}/xz/coder.c
    ${XZ_SRCDIR}/xz/coder.h
    ${XZ_SRCDIR}/xz/file_io.c
    ${XZ_SRCDIR}/xz/file_io.h
    ${XZ_SRCDIR}/xz/hardware.c
    ${XZ_SRCDIR}/xz/hardware.h
    ${XZ_SRCDIR}/xz/list.c
    ${XZ_SRCDIR}/xz/list.h
    ${XZ_SRCDIR}/xz/main.c
    ${XZ_SRCDIR}/xz/main.h
    ${XZ_SRCDIR}/xz/message.c
    ${XZ_SRCDIR}/xz/message.h
    ${XZ_SRCDIR}/xz/mytime.c
    ${XZ_SRCDIR}/xz/mytime.h
    ${XZ_SRCDIR}/xz/options.c
    ${XZ_SRCDIR}/xz/options.h
    ${XZ_SRCDIR}/xz/private.h
    ${XZ_SRCDIR}/xz/signals.c
    ${XZ_SRCDIR}/xz/signals.h
    ${XZ_SRCDIR}/xz/suffix.c
    ${XZ_SRCDIR}/xz/suffix.h
    ${XZ_SRCDIR}/xz/util.c
    ${XZ_SRCDIR}/xz/util.h
)

add_executable("xz" ${XZ_SOURCES})

target_link_libraries("xz" PRIVATE liblzma)
target_compile_definitions("xz" PRIVATE HAVE_CONFIG_H)
target_include_directories("xz" PRIVATE
    ${XZ_SRCDIR}/common
    ${XZ_SRCDIR}/liblzma/api
    .
)
