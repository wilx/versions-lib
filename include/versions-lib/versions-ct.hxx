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


#if defined (__FreeBSD__)
#define VERSIONS_LIB_HAS_SYS_TYPES_H 1
#define VERSIONS_LIB_HAS_SYS_SYSCTL_H 1
#define VERSIONS_LIB_HAS_SYS_PARAM_H 1
#endif

#if defined (VERSIONS_LIB_HAS_SYS_TYPES_H)
#include <sys/types.h>
#endif

#if defined (VERSIONS_LIB_HAS_SYS_SYSCTL_H)
#include <sys/sysctl.h>
#endif

#if defined (VERSIONS_LIB_HAS_SYS_PARAM_H)
#include <sys/param.h>
#endif

#endif // VERSIONS_LIB_VERSIONS_CT_HXX
