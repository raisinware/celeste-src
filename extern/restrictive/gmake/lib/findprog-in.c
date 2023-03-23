/* Locating a program in a given path.
   Copyright (C) 2001-2004, 2006-2023 Free Software Foundation, Inc.
   Written by Bruno Haible <haible@clisp.cons.org>, 2001, 2019.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */


#include "../../../../contrib/bin/gmake/config.h"

/* Specification.  */
#include "findprog.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "filename.h"
#include "concat-filename.h"

# define NATIVE_SLASH '/'
# define PATH_SEPARATOR ':'

/* The list of suffixes that the execlp/execvp function tries when searching
   for the program.  */
static const char * const suffixes[] =
  {
    ""
  };

const char *
find_in_given_path (const char *progname, const char *path,
                    const char *directory, bool optimize_for_exec)
{
  {
    bool has_slash = false;
    {
      const char *p;

      for (p = progname; *p != '\0'; p++)
        if (ISSLASH (*p))
          {
            has_slash = true;
            break;
          }
    }
    if (has_slash)
      {
        /* If progname contains a slash, it is either absolute or relative to
           the current directory.  PATH is not used.  */
        if (optimize_for_exec)
          /* The execl/execv/execlp/execvp functions will try the various
             suffixes anyway and fail if no executable is found.  */
          return progname;
        else
          {
            /* Try the various suffixes and see whether one of the files
               with such a suffix is actually executable.  */
            int failure_errno;
            size_t i;

            const char *directory_as_prefix =
              (directory != NULL && IS_RELATIVE_FILE_NAME (progname)
               ? directory
               : "");


            /* Try all platform-dependent suffixes.  */
            failure_errno = ENOENT;
            for (i = 0; i < sizeof (suffixes) / sizeof (suffixes[0]); i++)
              {
                const char *suffix = suffixes[i];

                  {
                    /* Concatenate directory_as_prefix, progname, suffix.  */
                    char *progpathname =
                      concatenated_filename (directory_as_prefix, progname,
                                             suffix);

                    if (progpathname == NULL)
                      return NULL; /* errno is set here */

                    /* On systems which have the eaccess() system call, let's
                       use it.  On other systems, let's hope that this program
                       is not installed setuid or setgid, so that it is ok to
                       call access() despite its design flaw.  */
                    if (eaccess (progpathname, X_OK) == 0)
                      {
                        /* Check that the progpathname does not point to a
                           directory.  */
                        struct stat statbuf;

                        if (stat (progpathname, &statbuf) >= 0)
                          {
                            if (! S_ISDIR (statbuf.st_mode))
                              {
                                /* Found!  */
                                if (strcmp (progpathname, progname) == 0)
                                  {
                                    free (progpathname);
                                    return progname;
                                  }
                                else
                                  return progpathname;
                              }

                            errno = EACCES;
                          }
                      }

                    if (errno != ENOENT)
                      failure_errno = errno;

                    free (progpathname);
                  }
              }

            errno = failure_errno;
            return NULL;
          }
      }
  }

  if (path == NULL)
    /* If PATH is not set, the default search path is implementation dependent.
       In practice, it is treated like an empty PATH.  */
    path = "";

  {
    /* Make a copy, to prepare for destructive modifications.  */
    char *path_copy = strdup (path);
    if (path_copy == NULL)
      return NULL; /* errno is set here */

    int failure_errno;
    char *path_rest;
    char *cp;


    failure_errno = ENOENT;
    for (path_rest = path_copy; ; path_rest = cp + 1)
      {
        const char *dir;
        bool last;
        char *dir_as_prefix_to_free;
        const char *dir_as_prefix;
        size_t i;

        /* Extract next directory in PATH.  */
        dir = path_rest;
        for (cp = path_rest; *cp != '\0' && *cp != PATH_SEPARATOR; cp++)
          ;
        last = (*cp == '\0');
        *cp = '\0';

        /* Empty PATH components designate the current directory.  */
        if (dir == cp)
          dir = ".";

        /* Concatenate directory and dir.  */
        if (directory != NULL && IS_RELATIVE_FILE_NAME (dir))
          {
            dir_as_prefix_to_free =
              concatenated_filename (directory, dir, NULL);
            if (dir_as_prefix_to_free == NULL)
              {
                /* errno is set here.  */
                failure_errno = errno;
                goto failed;
              }
            dir_as_prefix = dir_as_prefix_to_free;
          }
        else
          {
            dir_as_prefix_to_free = NULL;
            dir_as_prefix = dir;
          }

        /* Try all platform-dependent suffixes.  */
        for (i = 0; i < sizeof (suffixes) / sizeof (suffixes[0]); i++)
          {
            const char *suffix = suffixes[i];

              {
                /* Concatenate dir_as_prefix, progname, and suffix.  */
                char *progpathname =
                  concatenated_filename (dir_as_prefix, progname, suffix);

                if (progpathname == NULL)
                  {
                    /* errno is set here.  */
                    failure_errno = errno;
                    free (dir_as_prefix_to_free);
                    goto failed;
                  }

                /* On systems which have the eaccess() system call, let's
                   use it.  On other systems, let's hope that this program
                   is not installed setuid or setgid, so that it is ok to
                   call access() despite its design flaw.  */
                if (eaccess (progpathname, X_OK) == 0)
                  {
                    /* Check that the progpathname does not point to a
                       directory.  */
                    struct stat statbuf;

                    if (stat (progpathname, &statbuf) >= 0)
                      {
                        if (! S_ISDIR (statbuf.st_mode))
                          {
                            /* Found!  */
                            if (strcmp (progpathname, progname) == 0)
                              {
                                free (progpathname);

                                /* Add the "./" prefix for real, that
                                   concatenated_filename() optimized away.
                                   This avoids a second PATH search when the
                                   caller uses execl/execv/execlp/execvp.  */
                                progpathname =
                                  (char *) malloc (2 + strlen (progname) + 1);
                                if (progpathname == NULL)
                                  {
                                    /* errno is set here.  */
                                    failure_errno = errno;
                                    free (dir_as_prefix_to_free);
                                    goto failed;
                                  }
                                progpathname[0] = '.';
                                progpathname[1] = NATIVE_SLASH;
                                memcpy (progpathname + 2, progname,
                                        strlen (progname) + 1);
                              }

                            free (dir_as_prefix_to_free);
                            free (path_copy);
                            return progpathname;
                          }

                        errno = EACCES;
                      }
                  }

                if (errno != ENOENT)
                  failure_errno = errno;

                free (progpathname);
              }
          }

        free (dir_as_prefix_to_free);

        if (last)
          break;
      }

   failed:
    /* Not found in PATH.  */
    free (path_copy);

    errno = failure_errno;
    return NULL;
  }
}
