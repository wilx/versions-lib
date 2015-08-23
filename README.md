# versions-lib

The `versions-lib` provides means to check OS versions at compile time and at
run time.


## API

There are two headers:

- `versions-ct.hxx` -- Macros for checking versions prerequisites.

- `versions.hxx` -- Functions returning compile time and run time versions.

Functions and types are wrapped in `versionslib` namespace.


### `versions-ct.hxx`

This header defines the following macros. They are always defined, even on
different OSes. In such case they always expand to `0`.

- `VERSIONS_LIB_GLIBC_PREREQ(major, minor)`
- `VERSIONS_LIB_LINUX_PREREQ(major, minor, patch)`
- `VERSIONS_LIB_FREEBSD_PREREQ(major, minor)`
- `VERSIONS_LIB_NETBSD_PREREQ(major, minor, patch)`
- `VERSIONS_LIB_OPENBSD_PREREQ(major, minor)`
- `VERSIONS_LIB_CYGWIN_API_PREREQ(major, minor)`
- `VERSIONS_LIB_CYGWIN_DLL_PREREQ(major, minor, patch)`


### `versions.hxx`

This header contains functions that return compile time and run time versions
of OS. All of them return `version_triple`, even on different OS.

- `get_glibc_{ct,rt}_version ()`
- `get_linux_{ct,rt}_version ()`
- `get_freebsd_{ct,rt}_version ()`
- `get_netbsd_{ct,rt}_version ()`
- `get_openbsd_ct_version ()`
- `get_cygwin_{dll,api}_{ct,rt}_version ()`
