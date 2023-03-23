/* Basic filename support macros.
   Copyright (C) 2001-2023 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* From Paul Eggert and Jim Meyering.  */

#pragma once

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


/* Filename support.
   ISSLASH(C)                  tests whether C is a directory separator
                               character.
   HAS_DEVICE(Filename)        tests whether Filename contains a device
                               specification.
   FILE_SYSTEM_PREFIX_LEN(Filename)  length of the device specification
                                     at the beginning of Filename,
                                     index of the part consisting of
                                     alternating components and slashes.
   FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE
                               1 when a non-empty device specification
                               can be followed by an empty or relative
                               part,
                               0 when a non-empty device specification
                               must be followed by a slash,
                               0 when device specification don't exist.
   IS_ABSOLUTE_FILE_NAME(Filename)
                               tests whether Filename is independent of
                               any notion of "current directory".
   IS_RELATIVE_FILE_NAME(Filename)
                               tests whether Filename may be concatenated
                               to a directory filename.
   Note: On native Windows, OS/2, DOS, "c:" is neither an absolute nor a
   relative file name!
   IS_FILE_NAME_WITH_DIR(Filename)  tests whether Filename contains a device
                                    or directory specification.
 */
# define ISSLASH(C) ((C) == '/')
# define HAS_DEVICE(Filename) ((void) (Filename), 0)
# define FILE_SYSTEM_PREFIX_LEN(Filename) ((void) (Filename), 0)
# define FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE 0
# define IS_ABSOLUTE_FILE_NAME(Filename) ISSLASH ((Filename)[0])
# define IS_RELATIVE_FILE_NAME(Filename) (! ISSLASH ((Filename)[0]))
# define IS_FILE_NAME_WITH_DIR(Filename) (strchr ((Filename), '/') != NULL)

/* Deprecated macros.  For backward compatibility with old users of the
   'filename' module.  */
#define IS_ABSOLUTE_PATH IS_ABSOLUTE_FILE_NAME
#define IS_PATH_WITH_DIR IS_FILE_NAME_WITH_DIR


#ifdef __cplusplus
}
#endif
