#if ! defined (VERSIONS_LIB_VERSIONS_CT_HXX)
#define VERSIONS_LIB_VERSIONS_CT_HXX

#include <stdlib.h>

#define VERSIONS_LIB_COMBINE_VERSION(major, minor, patch)   \
    ((major) * 1000 * 1000 + (minor) * 1000 + (patch))

#if defined (__GNUC__)
#define VERSIONS_LIB_GCC_PREREQ(major, minor, patch)            \
    (VERSIONS_LIB_COMBINE_VERSION (__GNUC__, __GNUC_MINOR__,    \
        __GNUC_PATCHLEVEL__)                                    \
        >= VERSIONS_LIB_COMBINE_VERSION (major, minor, patch))
#else
#define VERSIONS_LIB_GCC_PREREQ(major, minor, patch) 0
#endif

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

#else // ! __GLIBC__
#define VERSIONS_LIB_GLIBC_PREREQ(major, minor) 0
#endif // __GLIBC__


#if defined (__linux__)
#if ! defined (LINUX_VERSION_CODE) \
    || ! defined (KERNEL_VERSION)
#include <linux/version.h>
#include <sys/utsname.h>
#endif
#define VERSIONS_LIB_LINUX_PREREQ(major, minor, patch) \
    (LINUX_VERSION_CODE >= KERNEL_VERSION(major, minor, patch))
#else // ! __linux__
#define VERSIONS_LIB_LINUX_PREREQ(major, minor, patch) 0
#endif // __linux__


#if defined (__FreeBSD__)                       \
    || defined (__NetBSD__)                     \
    || defined (__OpenBSD__)
#define VERSIONS_LIB_HAS_SYS_TYPES_H 1
#define VERSIONS_LIB_HAS_SYS_SYSCTL_H 1
#define VERSIONS_LIB_HAS_SYS_PARAM_H 1
#endif // __FreeBSD__ || __NetBSD__ || __OpenBSD__

#if defined (VERSIONS_LIB_HAS_SYS_TYPES_H)
#include <sys/types.h>
#endif

#if defined (VERSIONS_LIB_HAS_SYS_SYSCTL_H)
#include <sys/sysctl.h>
#endif

#if defined (VERSIONS_LIB_HAS_SYS_PARAM_H)
#include <sys/param.h>
#endif

#if defined (__FreeBSD__)
#define VERSIONS_LIB_FREEBSD_PREREQ(major, minor)               \
    (__FreeBSD_version >= (major) * 100000 + (minor) * 1000)
#else // ! __FreeBSD__
#define VERSIONS_LIB_FREEBSD_PREREQ(major, minor) 0
#endif // __FreeBSD__

#if defined (__NetBSD__)
#if defined (__NetBSD_Prereq__)
#define VERSIONS_LIB_NETBSD_PREREQ(major, minor, patch) \
    __NetBSD_Prereq__(major, minor, patch)
#else // !__NetBSD_Prereq__
#define VERSIONS_LIB_NETBSD_PREREQ(major, minor, patch) \
    (__NetBSD_Version__ >= (major) * 100000000          \
     + (minor) * 1000000 + (patch) * 100)
#endif // __NetBSD_Prereq__
#else // ! __NetBSD__
#define VERSIONS_LIB_NETBSD_PREREQ(major, minor, patch) 0
#endif // __NetBSD__

#if defined (__OpenBSD__)
#include <versions-lib/versions-ct-openbsd.hxx>
#define VERSIONS_LIB_OPENBSD_PREREQ(major, minor)           \
    (VERSIONS_LIB_OPENBSD_CT_MAJOR > (major)                \
        || ((major) == VERSIONS_LIB_OPENBSD_CT_MAJOR        \
            && VERSIONS_LIB_OPENBSD_CT_MINOR >= (minor)))
#else // ! __OpenBSD__
#define VERSIONS_LIB_OPENBSD_PREREQ(major, minor) 0
#endif // __OpenBSD__

#if defined (__CYGWIN__)
#include <cygwin/version.h>
#include <sys/cygwin.h>
#include <sys/utsname.h>
#define VERSIONS_LIB_CYGWIN_API_PREREQ(major, minor) \
    (CYGWIN_VERSION_API_MAJOR > major                \
        || (CYGWIN_VERSION_API_MAJOR == major        \
            && CYGWIN_VERSION_API_MINOR >= minor))
#define VERSIONS_LIB_CYGWIN_DLL_PREREQ(major, minor, patch)             \
    (CYGWIN_VERSION_DLL_COMBINED                                        \
        >= CYGWIN_VERSION_DLL_MAKE_COMBINED (major * 1000 + minor, patch))
#else // ! __CYGWIN__
#define VERSIONS_LIB_CYGWIN_API_PREREQ(major, minor) 0
#define VERSIONS_LIB_CYGWIN_DLL_PREREQ(major, minor, patch) 0
#endif // __CYGWIN__

#endif // VERSIONS_LIB_VERSIONS_CT_HXX
