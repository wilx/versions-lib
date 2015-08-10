#! env perl

use strict;

print "/* generated by $0 */\n";
for my $major (1..10) {
    for my $minor (0..9) {
        print <<"EOT"
#if defined (OpenBSD${major}_${minor})
#define VERSIONS_LIB_OPENBSD_CT_MAJOR $major
#define VERSIONS_LIB_OPENBSD_CT_MINOR $minor
#endif
EOT
    }
}

print <<"EOT"
#if ! defined (VERSIONS_LIB_OPENBSD_CT_MAJOR)
#error "VERSIONS_LIB_OPENBSD_CT_MAJOR not defined."
#endif
#if ! defined (VERSIONS_LIB_OPENBSD_CT_MINOR)
#error "VERSIONS_LIB_OPENBSD_CT_MINOR not defined."
#endif
EOT

