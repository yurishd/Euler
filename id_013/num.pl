#!/usr/bin/perl
die "give a file name\n" if !scalar @ARGV; 
open IN, $ARGV[0] or die "Could not open commands file: $ARGV[0]\n";
while (my $line = <IN>) {
    chomp $line;
    print "\"", $line, "\",\n";
}
 close IN;

