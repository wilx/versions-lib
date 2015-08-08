#if ! defined (VERSIONS_LIB_VERSIONS_HXX)
#define VERSIONS_LIB_VERSIONS_HXX

#include <versions-lib/versions-ct.hxx>

#include <tuple>
#include <sstream>
#include <string>
#include <limits>

#include <iostream>
#include <iomanip>

namespace versionlib {

using version_triple =
    std::tuple<unsigned short, unsigned short, unsigned short>;

version_triple const ZERO_VERSION {0, 0, 0};

inline
std::string
to_string (version_triple const & v)
{
    std::string str;
    str.reserve (15);

    str.append (std::to_string (std::get<0>(v)));
    str.push_back ('.');
    str.append (std::to_string (std::get<1>(v)));
    str.push_back ('.');
    str.append (std::to_string (std::get<2>(v)));

    return str;
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


} // namespace versionlib

#endif // VERSIONS_LIB_VERSIONS_HXX
