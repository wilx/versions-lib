#if ! defined (VERSIONS_LIB_VERSIONS_HXX)
#define VERSIONS_LIB_VERSIONS_HXX

#include <versions-lib/versions-ct.hxx>

#include <cerrno>
#include <cstdlib>
#include <tuple>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

#include <iostream>
#include <iomanip>

namespace versionslib {

using version_triple =
    std::tuple<unsigned short, unsigned short, unsigned short>;

version_triple const ZERO_VERSION {0, 0, 0};


inline
std::string
to_string (version_triple const & v)
{
    std::ostringstream oss;
    oss << std::get<0>(v) << '.' << std::get<1>(v) << '.' << std::get<2>(v);
    return oss.str ();
}


inline
version_triple
parse_version_triple (std::istream & istr, bool patch_ver_optional = true)
{
    unsigned short major;
    if ((istr >> major).fail ())
        return ZERO_VERSION;

    char ch;
    if ((istr >> ch).fail ()
        || ch != '.')
        return ZERO_VERSION;

    unsigned short minor;
    if ((istr >> minor).fail ())
        return ZERO_VERSION;

    unsigned short patch = 0;
    if (patch_ver_optional)
    {
        if (istr >> ch
            && ch == '.')
            istr >> patch;
    }
    else
    {
        if (! (istr >> ch
                && ch == '.'
                && (istr >> patch).good ()))
            return ZERO_VERSION;
    }

    return version_triple {major, minor, patch};
}


inline
version_triple
get_glibc_ct_version ()
{
#if defined (VERSIONS_LIB_GLIBC)
    return version_triple {__GLIBC__, __GLIBC_MINOR__, 0};
#else
    return ZERO_VERSION;
#endif
}


inline
version_triple
get_glibc_rt_version ()
{
#if defined (VERSIONS_LIB_GLIBC_HAS_gnu_get_libc_version)
    char const * const version_string = gnu_get_libc_version ();
    std::istringstream iss (version_string);
    unsigned short major;
    if ((iss >> major).fail ())
        return ZERO_VERSION;

    char ch;
    if ((iss >> ch).fail ()
        || ch != '.')
        return ZERO_VERSION;

    unsigned short minor;
    if ((iss >> minor).fail ())
        return ZERO_VERSION;

    unsigned short patch = 0;
    if (iss >> ch
        && ch == '.')
        iss >> patch;

    return version_triple {major, minor, patch};

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_linux_ct_version ()
{
#if defined (__linux__)
    unsigned short const major = LINUX_VERSION_CODE >> 16;
    unsigned short const minor = (LINUX_VERSION_CODE >> 8) & 0xFF;
    unsigned short const patch = LINUX_VERSION_CODE & 0xFF;

    return version_triple {major, minor, patch};

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_linux_rt_version ()
{
#if defined (__linux__)
    struct utsname name;
    int ret = uname (&name);
    if (ret == -1)
        return ZERO_VERSION;

    std::istringstream ifs (name.release);
    return parse_version_triple (ifs);

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_freebsd_ct_version ()
{
#if defined (__FreeBSD__) \
    && defined (__FreeBSD_version)
    unsigned short const major = __FreeBSD_version / 100000;
    unsigned short const minor = (__FreeBSD_version - major * 100000) / 1000;
    return version_triple {major, minor, 0};

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_freebsd_rt_version ()
{
#if defined (__FreeBSD__)
    std::string buf;
    buf.resize (20);

    int const kern_osrelease_mib[2] = { CTL_KERN, KERN_OSRELEASE };
    int retval;
    std::size_t len = buf.size ();
    while ((retval = sysctl (kern_osrelease_mib, 2, &buf[0], &len, nullptr,
                std::size_t (0)) == -1)
        && errno == ENOMEM)
    {
        buf.resize (buf.size () * 2 + 1);
        len = buf.size ();
    }

    if (retval != 0)
        return ZERO_VERSION;

    if (len != 0)
        buf.resize (len - 1);

    std::istringstream iss (buf);

    unsigned short major;
    if ((iss >> major).fail ())
        return ZERO_VERSION;

    char ch;
    if ((iss >> ch).fail ()
        || ch != '.')
        return ZERO_VERSION;

    unsigned short minor;
    if ((iss >> minor).fail ())
        return ZERO_VERSION;

    unsigned short patch = 0;
    if (iss >> ch
        && ch == '-')
    {
        iss.ignore (std::numeric_limits<std::streamsize>::max (), '-');
        if (iss
            && iss >> ch
            && ch == 'p')
        {
            iss >> patch;
        }
    }

    return version_triple {major, minor, patch};

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_netbsd_ct_version ()
{
#if defined (__NetBSD__) \
    && defined (__NetBSD_Version__)
    unsigned short const major = __NetBSD_Version__ / 100000000;
    unsigned short const minor = (__NetBSD_Version__ - major * 100000000) / 1000000;
    unsigned short const patch = (__NetBSD_Version__ - major * 100000000 - minor * 1000000) / 100;
    return version_triple {major, minor, patch};

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_netbsd_rt_version ()
{
#if defined (__NetBSD__)
    std::string buf;
    buf.resize (20);

    int const kern_osrelease_mib[2] = { CTL_KERN, KERN_OSRELEASE };
    int retval;
    std::size_t len = buf.size ();
    while ((retval = sysctl (kern_osrelease_mib, 2, &buf[0], &len, nullptr,
                std::size_t (0)) == -1)
        && errno == ENOMEM)
    {
        buf.resize (buf.size () * 2 + 1);
        len = buf.size ();
    }

    if (retval != 0)
        return ZERO_VERSION;

    if (len != 0)
        buf.resize (len - 1);

    std::istringstream iss (buf);
    return parse_version_triple (iss);

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_openbsd_ct_version ()
{
#if defined (__OpenBSD__)
    return version_triple {VERSIONS_LIB_OPENBSD_CT_MAJOR,
        VERSIONS_LIB_OPENBSD_CT_MINOR, 0};

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_openbsd_rt_version ()
{
#if defined (__OpenBSD__)
    std::string buf;
    buf.resize (20);

    int const kern_osrelease_mib[2] = { CTL_KERN, KERN_OSRELEASE };
    int retval;
    std::size_t len = buf.size ();
    while ((retval = sysctl (kern_osrelease_mib, 2, &buf[0], &len, nullptr,
                std::size_t (0)) == -1)
        && errno == ENOMEM)
    {
        buf.resize (buf.size () * 2 + 1);
        len = buf.size ();
    }

    if (retval != 0)
        return ZERO_VERSION;

    if (len != 0)
        buf.resize (len - 1);

    std::istringstream iss (buf);

    return parse_version_triple (iss);

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_cygwin_dll_ct_version ()
{
#if defined (__CYGWIN__)
    unsigned short const major = CYGWIN_VERSION_DLL_MAJOR / 1000;
    unsigned short const minor = CYGWIN_VERSION_DLL_MAJOR % 1000;
    unsigned short const patch = CYGWIN_VERSION_DLL_MINOR;

    return version_triple {major, minor, patch};

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_cygwin_api_ct_version ()
{
#if defined (__CYGWIN__)
    return version_triple {CYGWIN_VERSION_API_MAJOR, CYGWIN_VERSION_API_MINOR,
            0};

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_cygwin_dll_rt_version ()
{
#if defined (__CYGWIN__)
    struct utsname name;
    int ret = uname (&name);
    if (ret == -1)
        return ZERO_VERSION;

    std::istringstream ifs (name.release);
    return parse_version_triple (ifs);

#else
    return ZERO_VERSION;

#endif
}


inline
version_triple
get_cygwin_api_rt_version ()
{
#if defined (__CYGWIN__)
    struct utsname name;
    int ret = uname (&name);
    if (ret == -1)
        return ZERO_VERSION;

    std::istringstream ifs (name.release);
    ifs.ignore (std::numeric_limits<std::streamsize>::max (), '(');
    return parse_version_triple (ifs);

#else
    return ZERO_VERSION;

#endif
}

} // namespace versionslib

#endif // VERSIONS_LIB_VERSIONS_HXX
