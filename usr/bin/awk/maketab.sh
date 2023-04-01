#!/bin/sh
# SPDX-License-Identifier: Apache-2.0 OR MIT
# maketab.sh - generate proctab.c
set -x
set -e

CC="cc"
YACC="yacc"

AWK_SRCDIR="../../../extern/permissive/one-true-awk"

$YACC -d -b awkgram "${AWK_SRCDIR}/awkgram.y"
rm awkgram.tab.c
$CC -I. -o maketab "${AWK_SRCDIR}/maketab.c"

./maketab awkgram.tab.h > proctab.c
rm awkgram.tab.h
rm maketab
