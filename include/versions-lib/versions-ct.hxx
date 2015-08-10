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


#if defined (__FreeBSD__)                       \
    || defined (__NetBSD__)                     \
    || defined (__OpenBSD__)
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

#if defined (__NetBSD__)
#if defined (__NetBSD_Prereq__)
#define VERSIONS_LIB_NETBSD_PREREQ(major, minor, patch) \
    __NetBSD_Prereq__(major, minor, patch)
#else // !__NetBSD_Prereq__
#define VERSIONS_LIB_NETBSD_PREREQ(major, minor, patch) \
    (__NetBSD_Version__ >= (major) * 100000000          \
     + (minor) * 1000000 + (patch) * 100)
#endif // __NetBSD_Prereq__
#endif // __NetBSD__

#if defined (__OpenBSD__)
#include <versions-lib/versions-ct-openbsd.hxx>
#define VERSIONS_LIB_OPENBSD_PREREQ(major, minor)   \
    (VERSIONS_LIB_OPENBSD_CT_MAJOR > major          \
     || (major == VERSIONS_LIB_OPENBSD_CT_MAJOR     \
         && VERSIONS_LIB_OPENBSD_CT_MINOR >= minor))
#endif

#endif // VERSIONS_LIB_VERSIONS_CT_HXX
