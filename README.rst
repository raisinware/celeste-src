=============
Celeste Linux
=============
Welcome! This is the monorepo for the base userland of Celeste Linux, a
project for making a modern, clean, and open source Linux userland distribution
suitable for desktop, workstation, and server use.

Status
======
Critical parts of the userland (libc, build system, etc) are currently under
development, so nothing is currently functional at the moment.

Licensing
=========
New code contributed to this repo is licensed under the `ISC <LICENSE-ISC>`_,
and `Apache 2.0 <LICENSE-Apache>`_ licenses. 3rd-party code and modifications
to 3rd-party code will remain under their original licenses unless otherwise
specified. See `COPYRIGHT <COPYRIGHT.rst>`_ for details.

Special Thanks
==============
This list is in no particular order.

- `musl libc <https://www.musl-libc.org/>`_ (will be used as the base for the
  Celeste Linux libc)
- `ckati <https://github.com/google/kati>`_ (clean re-implementation of GNU
  Make that can export ninja files, will be used as the make implementation for
  building the kernel)
- `samurai <https://github.com/michaelforney/samurai>`_ (clean, simple, easily
  bootstrap-able ninja-compatible build tool that will be used for building the
  userland)
- `LLVM Project <https://llvm.org>`_ (For providing high-quality, modern, and
  clean C/C++ compilers and runtime libraries)
- `FreeBSD <https://freebsd.org>`_ (operating system with similar goals to
  Celeste, will also provide various utilities and commands [sh, diff, etc])
- `NetBSD <https://netbsd.org>`_ (for making a clean curses implementation,
  with a much better build system)

A very special thanks to my girlfriend
`@pocketlinux32 <https://github.com/pocketlinux32>`_ for inspiring me to start
this project, and for helping me before and along the way! Celeste Linux would
not be possible without her.
