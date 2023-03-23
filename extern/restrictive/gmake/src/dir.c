/* Directory hashing for GNU Make.
Copyright (C) 1988-2023 Free Software Foundation, Inc.
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

#include "makeint.h"
#include "hash.h"
#include "filedef.h"
#include "dep.h"
#include "debug.h"

#ifdef  HAVE_DIRENT_H
# include <dirent.h>
# define NAMLEN(dirent) strlen((dirent)->d_name)
#else
# define dirent direct
# define NAMLEN(dirent) (dirent)->d_namlen
# ifdef HAVE_SYS_NDIR_H
#  include <sys/ndir.h>
# endif
# ifdef HAVE_SYS_DIR_H
#  include <sys/dir.h>
# endif
# ifdef HAVE_NDIR_H
#  include <ndir.h>
# endif
# ifdef HAVE_VMSDIR_H
#  include "vmsdir.h"
# endif /* HAVE_VMSDIR_H */
#endif

/* In GNU systems, <dirent.h> defines this macro for us.  */
#ifdef _D_NAMLEN
# undef NAMLEN
# define NAMLEN(d) _D_NAMLEN(d)
#endif

#if (defined (POSIX) || defined (VMS) || defined (WINDOWS32)) && !defined (__GNU_LIBRARY__)
/* Posix does not require that the d_ino field be present, and some
   systems do not provide it. */
# define REAL_DIR_ENTRY(dp) 1
# define FAKE_DIR_ENTRY(dp)
#else
# define REAL_DIR_ENTRY(dp) (dp->d_ino != 0)
# define FAKE_DIR_ENTRY(dp) (dp->d_ino = 1)
#endif /* POSIX */




#ifdef HAVE_CASE_INSENSITIVE_FS
static const char *
downcase (const char *filename)
{
  static PATH_VAR (new_filename);
  char *df;

  if (filename == NULL)
    return NULL;

  df = new_filename;
  while (*filename != '\0')
    {
      *df++ = tolower ((unsigned char)*filename);
      ++filename;
    }

  *df = '\0';

  return new_filename;
}
#endif /* HAVE_CASE_INSENSITIVE_FS */


/* Never have more than this many directories open at once.  */

#define MAX_OPEN_DIRECTORIES 10

static unsigned int open_directories = 0;

/* Hash table of directories.  */

#ifndef DIRECTORY_BUCKETS
#define DIRECTORY_BUCKETS 199
#endif

struct directory_contents
  {
    dev_t dev;                  /* Device and inode numbers of this dir.  */
    ino_t ino;
    struct hash_table dirfiles; /* Files in this directory.  */
    unsigned long counter;      /* command_count value when last read. */
    DIR *dirstream;             /* Stream reading this directory.  */
  };

static struct directory_contents *
clear_directory_contents (struct directory_contents *dc)
{
  dc->counter = 0;
  if (dc->dirstream)
    {
      --open_directories;
      closedir (dc->dirstream);
      dc->dirstream = NULL;
    }
  if (dc->dirfiles.ht_vec != NULL)
    hash_free (&dc->dirfiles, 1);

  return NULL;
}

static unsigned long
directory_contents_hash_1 (const void *key_0)
{
  const struct directory_contents *key = key_0;
  unsigned long hash;

# ifdef VMS_INO_T
  hash = (((unsigned int) key->dev << 4)
          ^ ((unsigned int) key->ino[0]
             + (unsigned int) key->ino[1]
             + (unsigned int) key->ino[2]));
# else
  hash = ((unsigned int) key->dev << 4) ^ (unsigned int) key->ino;
# endif
  return hash;
}

static unsigned long
directory_contents_hash_2 (const void *key_0)
{
  const struct directory_contents *key = key_0;
  unsigned long hash;

# ifdef VMS_INO_T
  hash = (((unsigned int) key->dev << 4)
          ^ ~((unsigned int) key->ino[0]
              + (unsigned int) key->ino[1]
              + (unsigned int) key->ino[2]));
# else
  hash = ((unsigned int) key->dev << 4) ^ (unsigned int) ~key->ino;
# endif

  return hash;
}

/* Sometimes it's OK to use subtraction to get this value:
     result = X - Y;
   But, if we're not sure of the type of X and Y they may be too large for an
   int (on a 64-bit system for example).  So, use ?: instead.
   See Savannah bug #15534.

   NOTE!  This macro has side-effects!
*/

#define MAKECMP(_x,_y)  ((_x)<(_y)?-1:((_x)==(_y)?0:1))

static int
directory_contents_hash_cmp (const void *xv, const void *yv)
{
  const struct directory_contents *x = xv;
  const struct directory_contents *y = yv;
  int result;

# ifdef VMS_INO_T
  result = MAKECMP(x->ino[0], y->ino[0]);
  if (result)
    return result;
  result = MAKECMP(x->ino[1], y->ino[1]);
  if (result)
    return result;
  result = MAKECMP(x->ino[2], y->ino[2]);
  if (result)
    return result;
# else
  result = MAKECMP(x->ino, y->ino);
  if (result)
    return result;
# endif

  return MAKECMP(x->dev, y->dev);
}

/* Table of directory contents hashed by device and inode number.  */
static struct hash_table directory_contents;

struct directory
  {
    const char *name;           /* Name of the directory.  */
    unsigned long counter;      /* command_count value when last read.
                                   Used for non-existent directories.  */

    /* The directory's contents.  This data may be shared by several
       entries in the hash table, which refer to the same directory
       (identified uniquely by 'dev' and 'ino') under different names.  */
    struct directory_contents *contents;
  };

static unsigned long
directory_hash_1 (const void *key)
{
  return_ISTRING_HASH_1 (((const struct directory *) key)->name);
}

static unsigned long
directory_hash_2 (const void *key)
{
  return_ISTRING_HASH_2 (((const struct directory *) key)->name);
}

static int
directory_hash_cmp (const void *x, const void *y)
{
  return_ISTRING_COMPARE (((const struct directory *) x)->name,
                          ((const struct directory *) y)->name);
}

/* Table of directories hashed by name.  */
static struct hash_table directories;


/* Hash table of files in each directory.  */

struct dirfile
  {
    const char *name;           /* Name of the file.  */
    size_t length;
    short impossible;           /* This file is impossible.  */
    unsigned char type;
  };

static unsigned long
dirfile_hash_1 (const void *key)
{
  return_ISTRING_HASH_1 (((struct dirfile const *) key)->name);
}

static unsigned long
dirfile_hash_2 (const void *key)
{
  return_ISTRING_HASH_2 (((struct dirfile const *) key)->name);
}

static int
dirfile_hash_cmp (const void *xv, const void *yv)
{
  const struct dirfile *x = xv;
  const struct dirfile *y = yv;
  int result = (int) (x->length - y->length);
  if (result)
    return result;
  return_ISTRING_COMPARE (x->name, y->name);
}

#ifndef DIRFILE_BUCKETS
#define DIRFILE_BUCKETS 107
#endif

static int dir_contents_file_exists_p (struct directory *dir,
                                       const char *filename);
static struct directory *find_directory (const char *name);

/* Find the directory named NAME and return its 'struct directory'.  */

static struct directory *
find_directory (const char *name)
{
  struct directory *dir;
  struct directory **dir_slot;
  struct directory dir_key;
  struct directory_contents *dc;
  struct directory_contents **dc_slot;
  struct directory_contents dc_key;

  struct stat st;
  int r;

  dir_key.name = name;
  dir_slot = (struct directory **) hash_find_slot (&directories, &dir_key);
  dir = *dir_slot;

  if (!HASH_VACANT (dir))
    {
      unsigned long ctr = dir->contents ? dir->contents->counter : dir->counter;

      /* No commands have run since we parsed this directory so it's good.  */
      if (ctr == command_count)
        return dir;

      DB (DB_VERBOSE, ("Directory %s cache invalidated (count %lu != command %lu)\n",
                       name, ctr, command_count));

      if (dir->contents)
        clear_directory_contents (dir->contents);
    }
  else
    {
      /* The directory was not found.  Create a new entry for it.  */
      size_t len = strlen (name);

      dir = xmalloc (sizeof (struct directory));
      dir->name = strcache_add_len (name, len);
      hash_insert_at (&directories, dir, dir_slot);
    }

  dir->contents = NULL;
  dir->counter = command_count;

  /* See if the directory exists.  */
  EINTRLOOP (r, stat (name, &st));

  if (r < 0)
    /* Couldn't stat the directory; nothing else to do.  */
    return dir;

  /* Search the contents hash table; device and inode are the key.  */

  memset (&dc_key, '\0', sizeof (dc_key));
  dc_key.dev = st.st_dev;
# ifdef VMS_INO_T
  dc_key.ino[0] = st.st_ino[0];
  dc_key.ino[1] = st.st_ino[1];
  dc_key.ino[2] = st.st_ino[2];
# else
  dc_key.ino = st.st_ino;
# endif
  dc_slot = (struct directory_contents **) hash_find_slot (&directory_contents, &dc_key);
  dc = *dc_slot;

  if (HASH_VACANT (dc))
    {
      /* Nope; this really is a directory we haven't seen before.  */
      /* Enter it in the contents hash table.  */
      dc = xcalloc (sizeof (struct directory_contents));
      *dc = dc_key;


      hash_insert_at (&directory_contents, dc, dc_slot);
    }

  /* Point the name-hashed entry for DIR at its contents data.  */
  dir->contents = dc;

  /* If the contents have changed, we need to reseed.  */
  if (dc->counter != command_count)
    {
      if (dc->counter)
        clear_directory_contents (dc);

      dc->counter = command_count;

      ENULLLOOP (dc->dirstream, opendir (name));
      if (dc->dirstream == NULL)
        /* Couldn't open the directory: mark this by setting files to NULL.  */
        dc->dirfiles.ht_vec = NULL;
      else
        {
          hash_init (&dc->dirfiles, DIRFILE_BUCKETS,
                     dirfile_hash_1, dirfile_hash_2, dirfile_hash_cmp);
          /* Keep track of how many directories are open.  */
          ++open_directories;
          if (open_directories == MAX_OPEN_DIRECTORIES)
            /* We have too many directories open already.
               Read the entire directory and then close it.  */
            dir_contents_file_exists_p (dir, NULL);
        }
    }

  return dir;
}

/* Return 1 if the name FILENAME is entered in DIR's hash table.
   FILENAME must contain no slashes.  */

static int
dir_contents_file_exists_p (struct directory *dir,
                            const char *filename)
{
  struct dirfile *df;
  struct dirent *d;
  struct directory_contents *dc = dir->contents;

  if (dc == NULL || dc->dirfiles.ht_vec == NULL)
    /* The directory could not be stat'd or opened.  */
    return 0;


#ifdef HAVE_CASE_INSENSITIVE_FS
  filename = downcase (filename);
#endif

  if (filename != NULL)
    {
      struct dirfile dirfile_key;

      if (*filename == '\0')
        {
          /* Checking if the directory exists.  */
          return 1;
        }
      dirfile_key.name = filename;
      dirfile_key.length = strlen (filename);
      df = hash_find_item (&dc->dirfiles, &dirfile_key);
      if (df)
        return !df->impossible;
    }

  /* The file was not found in the hashed list.
     Try to read the directory further.  */

  if (dc->dirstream == NULL)
    {
        /* The directory has been all read in.  */
        return 0;
    }

  while (1)
    {
      /* Enter the file in the hash table.  */
      size_t len;
      struct dirfile dirfile_key;
      struct dirfile **dirfile_slot;

      ENULLLOOP (d, readdir (dc->dirstream));
      if (d == NULL)
        {
          if (errno)
            OSS (fatal, NILF, "readdir %s: %s", dir->name, strerror (errno));
          break;
        }

      if (!REAL_DIR_ENTRY (d))
        continue;

      len = NAMLEN (d);
      dirfile_key.name = d->d_name;
      dirfile_key.length = len;
      dirfile_slot = (struct dirfile **) hash_find_slot (&dc->dirfiles, &dirfile_key);
        {
          df = xmalloc (sizeof (struct dirfile));
          df->name = strcache_add_len (d->d_name, len);
#ifdef HAVE_STRUCT_DIRENT_D_TYPE
          df->type = d->d_type;
#endif
          df->length = len;
          df->impossible = 0;
          hash_insert_at (&dc->dirfiles, df, dirfile_slot);
        }
      /* Check if the name matches the one we're searching for.  */
      if (filename != NULL && patheq (d->d_name, filename))
        return 1;
    }

  /* If the directory has been completely read in,
     close the stream and reset the pointer to nil.  */
  if (d == NULL)
    {
      --open_directories;
      closedir (dc->dirstream);
      dc->dirstream = NULL;
    }

  return 0;
}

/* Return 1 if the name FILENAME in directory DIRNAME
   is entered in the dir hash table.
   FILENAME must contain no slashes.  */

int
dir_file_exists_p (const char *dirname, const char *filename)
{
  return dir_contents_file_exists_p (find_directory (dirname),
                                     filename);
}

/* Return 1 if the file named NAME exists.  */

int
file_exists_p (const char *name)
{
  const char *dirend;
  const char *dirname;
  const char *slash;

#ifndef NO_ARCHIVES
  if (ar_name (name))
    return ar_member_date (name) != (time_t) -1;
#endif

  dirend = strrchr (name, '/');
  if (dirend == NULL)
    return dir_file_exists_p (".", name);

  slash = dirend;
  if (dirend == name)
    dirname = "/";
  else
    {
      char *p;
      p = alloca (dirend - name + 1);
      memcpy (p, name, dirend - name);
      p[dirend - name] = '\0';
      dirname = p;
    }
  slash++;
  return dir_file_exists_p (dirname, slash);
}

/* Mark FILENAME as 'impossible' for 'file_impossible_p'.
   This means an attempt has been made to search for FILENAME
   as an intermediate file, and it has failed.  */

void
file_impossible (const char *filename)
{
  const char *dirend;
  const char *p = filename;
  struct directory *dir;
  struct dirfile *new;

  dirend = strrchr (p, '/');
  if (dirend == NULL)
    dir = find_directory (".");
  else
    {
      const char *dirname;
      const char *slash = dirend;
      if (dirend == p)
        dirname = "/";
      else
        {
          char *cp;
          cp = alloca (dirend - p + 1);
          memcpy (cp, p, dirend - p);
          cp[dirend - p] = '\0';
          dirname = cp;
        }
      dir = find_directory (dirname);
      filename = p = slash + 1;
    }

  if (dir->contents == NULL)
    /* The directory could not be stat'd.  We allocate a contents
       structure for it, but leave it out of the contents hash table.  */
    dir->contents = xcalloc (sizeof (struct directory_contents));

  if (dir->contents->dirfiles.ht_vec == NULL)
    hash_init (&dir->contents->dirfiles, DIRFILE_BUCKETS,
               dirfile_hash_1, dirfile_hash_2, dirfile_hash_cmp);

  /* Make a new entry and put it in the table.  */

  new = xmalloc (sizeof (struct dirfile));
  new->length = strlen (filename);
  new->name = strcache_add_len (filename, new->length);
  new->impossible = 1;
  hash_insert (&dir->contents->dirfiles, new);
}

/* Return nonzero if FILENAME has been marked impossible.  */

int
file_impossible_p (const char *filename)
{
  const char *dirend;
  struct directory_contents *dir;
  struct dirfile *dirfile;
  struct dirfile dirfile_key;

  dirend = strrchr (filename, '/');
  if (dirend == NULL)
    dir = find_directory (".")->contents;
  else
    {
      const char *dirname;
      const char *slash = dirend;
      if (dirend == filename)
        dirname = "/";
      else
        {
          char *cp;
          cp = alloca (dirend - filename + 1);
          memcpy (cp, filename, dirend - filename);
          cp[dirend - filename] = '\0';
          dirname = cp;
        }
      dir = find_directory (dirname)->contents;
      filename = slash + 1;
    }

  if (dir == NULL || dir->dirfiles.ht_vec == NULL)
    /* There are no files entered for this directory.  */
    return 0;

#ifdef HAVE_CASE_INSENSITIVE_FS
  filename = downcase (filename);
#endif

  dirfile_key.name = filename;
  dirfile_key.length = strlen (filename);
  dirfile = hash_find_item (&dir->dirfiles, &dirfile_key);
  if (dirfile)
    return dirfile->impossible;

  return 0;
}

/* Return the already allocated name in the
   directory hash table that matches DIR.  */

const char *
dir_name (const char *dir)
{
  return find_directory (dir)->name;
}

/* Print the data base of directories.  */

void
print_dir_data_base (void)
{
  unsigned int files;
  unsigned int impossible;
  struct directory **dir_slot;
  struct directory **dir_end;

  puts (_("\n# Directories\n"));

  files = impossible = 0;

  dir_slot = (struct directory **) directories.ht_vec;
  dir_end = dir_slot + directories.ht_size;
  for ( ; dir_slot < dir_end; dir_slot++)
    {
      struct directory *dir = *dir_slot;
      if (! HASH_VACANT (dir))
        {
          if (dir->contents == NULL)
            printf (_("# %s: could not be stat'd.\n"), dir->name);
          else if (dir->contents->dirfiles.ht_vec == NULL)
            printf (_("# %s (device %ld, inode %ld): could not be opened.\n"),
                    dir->name, (long) dir->contents->dev, (long) dir->contents->ino);
          else
            {
              unsigned int f = 0;
              unsigned int im = 0;
              struct dirfile **files_slot;
              struct dirfile **files_end;

              files_slot = (struct dirfile **) dir->contents->dirfiles.ht_vec;
              files_end = files_slot + dir->contents->dirfiles.ht_size;
              for ( ; files_slot < files_end; files_slot++)
                {
                  struct dirfile *df = *files_slot;
                  if (! HASH_VACANT (df))
                    {
                      if (df->impossible)
                        ++im;
                      else
                        ++f;
                    }
                }
              printf (_("# %s (device %ld, inode %ld): "), dir->name,
                      (long)dir->contents->dev, (long)dir->contents->ino);
              if (f == 0)
                fputs (_("No"), stdout);
              else
                printf ("%u", f);
              fputs (_(" files, "), stdout);
              if (im == 0)
                fputs (_("no"), stdout);
              else
                printf ("%u", im);
              fputs (_(" impossibilities"), stdout);
              if (dir->contents->dirstream == NULL)
                puts (".");
              else
                puts (_(" so far."));
              files += f;
              impossible += im;
            }
        }
    }

  fputs ("\n# ", stdout);
  if (files == 0)
    fputs (_("No"), stdout);
  else
    printf ("%u", files);
  fputs (_(" files, "), stdout);
  if (impossible == 0)
    fputs (_("no"), stdout);
  else
    printf ("%u", impossible);
  printf (_(" impossibilities in %lu directories.\n"), directories.ht_fill);
}

/* Hooks for globbing.  */

/* Structure describing state of iterating through a directory hash table.  */

struct dirstream
  {
    struct directory_contents *contents; /* The directory being read.  */
    struct dirfile **dirfile_slot; /* Current slot in table.  */
  };

void*
open_dirstream (const char *directory)
{
  struct dirstream *new;
  struct directory *dir = find_directory (directory);

  if (dir->contents == NULL || dir->contents->dirfiles.ht_vec == NULL)
    /* DIR->contents is nil if the directory could not be stat'd.
       DIR->contents->dirfiles is nil if it could not be opened.  */
    return NULL;

  /* Read all the contents of the directory now.  There is no benefit
     in being lazy, since glob will want to see every file anyway.  */

  dir_contents_file_exists_p (dir, NULL);

  new = xmalloc (sizeof (struct dirstream));
  new->contents = dir->contents;
  new->dirfile_slot = (struct dirfile **) new->contents->dirfiles.ht_vec;

  return new;
}

struct dirent*
read_dirstream (void *stream)
{
  static char *buf;
  static size_t bufsz;

  struct dirstream *const ds = (struct dirstream *) stream;
  struct directory_contents *dc = ds->contents;
  struct dirfile **dirfile_end = (struct dirfile **) dc->dirfiles.ht_vec + dc->dirfiles.ht_size;

  while (ds->dirfile_slot < dirfile_end)
    {
      struct dirfile *df = *ds->dirfile_slot++;
      if (! HASH_VACANT (df) && !df->impossible)
        {
          /* The glob interface wants a 'struct dirent', so mock one up.  */
          struct dirent *d;
          size_t len = df->length + 1;
          size_t sz = sizeof (*d) - sizeof (d->d_name) + len;
          if (sz > bufsz)
            {
              bufsz *= 2;
              if (sz > bufsz)
                bufsz = sz;
              buf = xrealloc (buf, bufsz);
            }
          d = (struct dirent *) buf;
          FAKE_DIR_ENTRY (d);
#ifdef _DIRENT_HAVE_D_NAMLEN
          d->d_namlen = len - 1;
#endif
#ifdef HAVE_STRUCT_DIRENT_D_TYPE
          d->d_type = df->type;
#endif
          memcpy (d->d_name, df->name, len);
          return d;
        }
    }

  return NULL;
}

void dir_setup_glob (gmake_glob_t *gl) {
  gl->gl_offs = 0;
}

void
hash_init_directories (void)
{
  hash_init (&directories, DIRECTORY_BUCKETS,
             directory_hash_1, directory_hash_2, directory_hash_cmp);
  hash_init (&directory_contents, DIRECTORY_BUCKETS,
             directory_contents_hash_1, directory_contents_hash_2,
             directory_contents_hash_cmp);
}
