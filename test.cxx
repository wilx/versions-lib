#include <versions-lib/versions.hxx>
#include <iostream>
#include <iomanip>

namespace v = versionslib;

int
main ()
{
    struct utsname name;
    uname (&name);
    std::cout << "release: " << name.release << "\n"
              << "version: " << name.version << "\n";

    v::version_triple glibc_ct_version = v::get_glibc_ct_version ();
    v::version_triple glibc_rt_version = v::get_glibc_rt_version ();
    std::cout << "glibc compile time version: "
              << v::to_string (glibc_ct_version) << "\n"
              << "glibc run time version: "
              << v::to_string (glibc_rt_version) << "\n";

    v::version_triple linux_ct_version = v::get_linux_ct_version ();
    v::version_triple linux_rt_version = v::get_linux_rt_version ();
    std::cout << "Linux compile time version: "
              << v::to_string (linux_ct_version) << "\n"
              << "Linux run time version: "
              << v::to_string (linux_rt_version) << "\n";

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

    v::version_triple cygwin_dll_ct_version = v::get_cygwin_dll_ct_version ();
    v::version_triple cygwin_dll_rt_version = v::get_cygwin_dll_rt_version ();
    std::cout << "Cygwin DLL compile time version: "
              << v::to_string (cygwin_dll_ct_version) << "\n"
              << "Cygwin DLL run time version: "
              << v::to_string (cygwin_dll_rt_version) << "\n";

    v::version_triple cygwin_api_ct_version = v::get_cygwin_api_ct_version ();
    v::version_triple cygwin_api_rt_version = v::get_cygwin_api_rt_version ();
    std::cout << "Cygwin API compile time version: "
              << v::to_string (cygwin_api_ct_version) << "\n"
              << "Cygwin API run time version: "
              << v::to_string (cygwin_api_rt_version) << "\n";
}
