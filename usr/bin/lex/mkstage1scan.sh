#!/bin/sh
# SPDX-License-Identifier: Apache-2.0 OR ISC
# mkstage1scan.sh - generate stage1scan.c

FLEX_SRCDIR="../../../extern/permissive/flex/src"

sed 's|^\(#line .*\)"'$(printf %s scan.c | sed 's|[][\\\\.*]|\\\\&|g')'"|\1"$@"|g' \
    "${FLEX_SRCDIR}/scan.c" > stage1scan.c
