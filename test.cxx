#include <versions-lib/versions.hxx>
#include <iostream>
#include <iomanip>

namespace v = versionlib;

int
main ()
{
    v::version_triple glibc_ct_version = v::get_glibc_ct_version ();
    v::version_triple glibc_rt_version = v::get_glibc_rt_version ();
    std::cout << "glibc compile time version: "
              << v::to_string (glibc_ct_version) << "\n"
              << "glibc run time version: "
              << v::to_string (glibc_rt_version) << "\n";


    v::version_triple freebsd_ct_version = v::get_freebsd_ct_version ();
    v::version_triple freebsd_rt_version = v::get_freebsd_rt_version ();
    std::cout << "FreeBSD compile time version: "
              << v::to_string (freebsd_ct_version) << "\n"
              << "FreeBSD run time version: "
              << v::to_string (freebsd_rt_version) << "\n";

    v::version_triple netbsd_ct_version = v::get_netbsd_ct_version ();
    v::version_triple netbsd_rt_version = v::get_netbsd_rt_version ();
    std::cout << "NetBSD compile time version: "
              << v::to_string (netbsd_ct_version) << "\n"
              << "NetBSD run time version: "
              << v::to_string (netbsd_rt_version) << "\n";

    v::version_triple openbsd_ct_version = v::get_openbsd_ct_version ();
    v::version_triple openbsd_rt_version = v::get_openbsd_rt_version ();
    std::cout << "OpenBSD compile time version: "
              << v::to_string (openbsd_ct_version) << "\n"
              << "OpenBSD run time version: "
              << v::to_string (openbsd_rt_version) << "\n";
}
