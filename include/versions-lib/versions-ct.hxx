#if ! defined (VERSIONS_LIB_VERSIONS_CT_HXX)
#define VERSIONS_LIB_VERSIONS_CT_HXX

#include <stdlib.h>

#if defined (__GLIBC__) \
    || defined (__GNU_LIBRARY__)

#define VERSIONS_LIB_GLIBC 1

#if defined (__GLIBC_PREREQ)
#define VERSIONS_LIB_GLIBC_PREREQ(major, minor) __GLIBC_PREREQ(major, minor)
#else
#define VERSIONS_LIB_GLIBC_PREREQ(major, minor)                         \
    ((__GLIBC__ << 16) + __GLIBC_MINOR__ >= ((major) << 16) + (minor))
#endif

#if VERSIONS_LIB_GLIBC_PREREQ(2, 1)
#define VERSIONS_LIB_GLIBC_HAS_gnu_get_libc_version 1
#include <gnu/libc-version.h>
#endif

#endif // __GLIBC__

#endif // VERSIONS_LIB_VERSIONS_CT_HXX
