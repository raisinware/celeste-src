/* Miscellaneous global declarations and portability cruft for GNU Make.
Copyright (C) 2023 Free Software Foundation, Inc.
This file is part of GNU Make.

GNU Make is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 3 of the License, or (at your option) any later
version.

GNU Make is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <https://www.gnu.org/licenses/>.  */

/*
  This file is included at the end of config.h

   That means it's included _everywhere_ as the first thing,
   INCLUDING content imported from gnulib.  BE AWARE!!
*/

#pragma once

#include "../../../../contrib/bin/gmake/config.h"

#undef  HAVE_CONFIG_H
#define HAVE_CONFIG_H 1

/* Specify we want GNU source code.  This must be defined before any
   system headers are included.  */

#define _GNU_SOURCE 1

/* AIX requires this to be the first thing in the file.  */
# include <alloca.h>

/* Declare function prototypes for src/misc.c functions if needed.  */

#include <stddef.h>
