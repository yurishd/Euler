#!/usr/bin/perl

use strict;
use warnings;

foreach my $dn (`ls -1`) {
    chomp $dn;
    if (-d $dn) {
        if ($dn =~ /id_(\d{2})$/) {
            my $newdn = "id_0$1";
            print "$dn -> $newdn yes\n";
            `mv $dn $newdn`
        } else {
            print "$dn no\n";
        }
    }
}
