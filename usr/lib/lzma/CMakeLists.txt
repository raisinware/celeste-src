# SPDX-License-Identifier: Apache-2.0 OR ISC

set(LIBLZMA_VERSION "5.4.2")
set(LIBLZMA_SRCDIR "${CMAKE_SOURCE_DIR}/extern/publicdomain/xz-utils/src")

set(LIBLZMA_SOURCES
    config.h
    ${LIBLZMA_SRCDIR}/common/mythread.h
    ${LIBLZMA_SRCDIR}/common/sysdefs.h
    ${LIBLZMA_SRCDIR}/common/tuklib_common.h
    ${LIBLZMA_SRCDIR}/common/tuklib_config.h
    ${LIBLZMA_SRCDIR}/common/tuklib_cpucores.c
    ${LIBLZMA_SRCDIR}/common/tuklib_cpucores.h
    ${LIBLZMA_SRCDIR}/common/tuklib_integer.h
    ${LIBLZMA_SRCDIR}/common/tuklib_physmem.c
    ${LIBLZMA_SRCDIR}/common/tuklib_physmem.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/base.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/bcj.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/block.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/check.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/container.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/delta.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/filter.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/hardware.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/index.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/index_hash.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/lzma12.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/stream_flags.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/version.h
    ${LIBLZMA_SRCDIR}/liblzma/api/lzma/vli.h
    ${LIBLZMA_SRCDIR}/liblzma/check/check.c
    ${LIBLZMA_SRCDIR}/liblzma/check/check.h
    ${LIBLZMA_SRCDIR}/liblzma/check/crc32_fast.c
    ${LIBLZMA_SRCDIR}/liblzma/check/crc32_table.c
    ${LIBLZMA_SRCDIR}/liblzma/check/crc32_table_be.h
    ${LIBLZMA_SRCDIR}/liblzma/check/crc32_table_le.h
    ${LIBLZMA_SRCDIR}/liblzma/check/crc64_fast.c
    ${LIBLZMA_SRCDIR}/liblzma/check/crc64_table.c
    ${LIBLZMA_SRCDIR}/liblzma/check/crc64_table_be.h
    ${LIBLZMA_SRCDIR}/liblzma/check/crc64_table_le.h
    ${LIBLZMA_SRCDIR}/liblzma/check/crc_macros.h
    ${LIBLZMA_SRCDIR}/liblzma/check/sha256.c
    ${LIBLZMA_SRCDIR}/liblzma/common/alone_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/alone_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/alone_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/auto_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/block_buffer_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/block_buffer_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/block_buffer_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/block_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/block_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/block_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/block_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/block_header_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/block_header_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/block_util.c
    ${LIBLZMA_SRCDIR}/liblzma/common/common.c
    ${LIBLZMA_SRCDIR}/liblzma/common/common.h
    ${LIBLZMA_SRCDIR}/liblzma/common/easy_buffer_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/easy_decoder_memusage.c
    ${LIBLZMA_SRCDIR}/liblzma/common/easy_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/easy_encoder_memusage.c
    ${LIBLZMA_SRCDIR}/liblzma/common/easy_preset.c
    ${LIBLZMA_SRCDIR}/liblzma/common/easy_preset.h
    ${LIBLZMA_SRCDIR}/liblzma/common/file_info.c
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_buffer_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_buffer_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_common.c
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_common.h
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_flags_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/filter_flags_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/hardware_cputhreads.c
    ${LIBLZMA_SRCDIR}/liblzma/common/hardware_physmem.c
    ${LIBLZMA_SRCDIR}/liblzma/common/index.c
    ${LIBLZMA_SRCDIR}/liblzma/common/index.h
    ${LIBLZMA_SRCDIR}/liblzma/common/index_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/index_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/index_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/index_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/index_hash.c
    ${LIBLZMA_SRCDIR}/liblzma/common/lzip_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/lzip_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/memcmplen.h
    ${LIBLZMA_SRCDIR}/liblzma/common/microlzma_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/microlzma_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/outqueue.c
    ${LIBLZMA_SRCDIR}/liblzma/common/outqueue.h
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_buffer_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_buffer_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_decoder_mt.c
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_encoder_mt.c
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_flags_common.c
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_flags_common.h
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_flags_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/stream_flags_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/string_conversion.c
    ${LIBLZMA_SRCDIR}/liblzma/common/vli_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/vli_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/common/vli_size.c
    ${LIBLZMA_SRCDIR}/liblzma/delta/delta_common.c
    ${LIBLZMA_SRCDIR}/liblzma/delta/delta_common.h
    ${LIBLZMA_SRCDIR}/liblzma/delta/delta_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/delta/delta_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/delta/delta_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/delta/delta_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/delta/delta_private.h
    ${LIBLZMA_SRCDIR}/liblzma/lz/lz_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/lz/lz_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/lz/lz_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/lz/lz_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/lz/lz_encoder_hash.h
    ${LIBLZMA_SRCDIR}/liblzma/lz/lz_encoder_hash_table.h
    ${LIBLZMA_SRCDIR}/liblzma/lz/lz_encoder_mf.c
    ${LIBLZMA_SRCDIR}/liblzma/lzma/fastpos.h
    ${LIBLZMA_SRCDIR}/liblzma/lzma/fastpos_table.c
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma2_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma2_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma2_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma2_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma_common.h
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma_encoder_optimum_fast.c
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma_encoder_optimum_normal.c
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma_encoder_presets.c
    ${LIBLZMA_SRCDIR}/liblzma/lzma/lzma_encoder_private.h
    ${LIBLZMA_SRCDIR}/liblzma/rangecoder/price.h
    ${LIBLZMA_SRCDIR}/liblzma/rangecoder/price_table.c
    ${LIBLZMA_SRCDIR}/liblzma/rangecoder/range_common.h
    ${LIBLZMA_SRCDIR}/liblzma/rangecoder/range_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/rangecoder/range_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/simple/arm.c
    ${LIBLZMA_SRCDIR}/liblzma/simple/armthumb.c
    ${LIBLZMA_SRCDIR}/liblzma/simple/arm64.c
    ${LIBLZMA_SRCDIR}/liblzma/simple/ia64.c
    ${LIBLZMA_SRCDIR}/liblzma/simple/powerpc.c
    ${LIBLZMA_SRCDIR}/liblzma/simple/simple_coder.c
    ${LIBLZMA_SRCDIR}/liblzma/simple/simple_coder.h
    ${LIBLZMA_SRCDIR}/liblzma/simple/simple_decoder.c
    ${LIBLZMA_SRCDIR}/liblzma/simple/simple_decoder.h
    ${LIBLZMA_SRCDIR}/liblzma/simple/simple_encoder.c
    ${LIBLZMA_SRCDIR}/liblzma/simple/simple_encoder.h
    ${LIBLZMA_SRCDIR}/liblzma/simple/simple_private.h
    ${LIBLZMA_SRCDIR}/liblzma/simple/sparc.c
    ${LIBLZMA_SRCDIR}/liblzma/simple/x86.c
)

# shared library
add_library("liblzma" SHARED "${LIBLZMA_SOURCES}")
set_target_properties("liblzma" PROPERTIES C_VISIBILITY_PRESET hidden
                                           LINK_DEPENDS "${LIBLZMA_SRCDIR}/liblzma/liblzma_linux.map"
                                           VERSION ${LIBLZMA_VERSION}
                                           SOVERSION "5")
target_compile_definitions("liblzma" PRIVATE HAVE_CONFIG_H HAVE_VISIBILITY=1)
target_include_directories("liblzma" PRIVATE
    ${LIBLZMA_SRCDIR}/liblzma/api
    ${LIBLZMA_SRCDIR}/liblzma/common
    ${LIBLZMA_SRCDIR}/liblzma/check
    ${LIBLZMA_SRCDIR}/liblzma/lz
    ${LIBLZMA_SRCDIR}/liblzma/rangecoder
    ${LIBLZMA_SRCDIR}/liblzma/lzma
    ${LIBLZMA_SRCDIR}/liblzma/delta
    ${LIBLZMA_SRCDIR}/liblzma/simple
    ${LIBLZMA_SRCDIR}/common
    .
)
target_link_options(liblzma PRIVATE
        "-Wl,--version-script=${LIBLZMA_SRCDIR}/liblzma/liblzma_linux.map")

# static library
add_library("liblzmastatic" STATIC "${LIBLZMA_SOURCES}")
target_compile_definitions("liblzmastatic" PRIVATE HAVE_CONFIG_H HAVE_VISIBILITY=0)
target_include_directories("liblzmastatic" PRIVATE .)
target_include_directories("liblzmastatic" PRIVATE
    ${LIBLZMA_SRCDIR}/liblzma/api
    ${LIBLZMA_SRCDIR}/liblzma/common
    ${LIBLZMA_SRCDIR}/liblzma/check
    ${LIBLZMA_SRCDIR}/liblzma/lz
    ${LIBLZMA_SRCDIR}/liblzma/rangecoder
    ${LIBLZMA_SRCDIR}/liblzma/lzma
    ${LIBLZMA_SRCDIR}/liblzma/delta
    ${LIBLZMA_SRCDIR}/liblzma/simple
    ${LIBLZMA_SRCDIR}/common
    .
)

set_target_properties("liblzma" "liblzmastatic" PROPERTIES OUTPUT_NAME "lzma")
