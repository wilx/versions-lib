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

    v::version_triple freebsd_rt_version = v::get_freebsd_rt_version ();
    std::cout << "FreeBSD run time version: "
              << v::to_string (freebsd_rt_version) << "\n";
}
