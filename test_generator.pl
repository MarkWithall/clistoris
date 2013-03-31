#!/usr/bin/env perl

use strict;
use warnings;
use Carp;
use Template;

croak "Usage: $0 <test.c>" unless (@ARGV == 1);

my $fixture = $ARGV[0];
$fixture =~ s/\.c$//;

my @tests = ();

open (FILE, $ARGV[0]) || croak $!;
while (my $line = <FILE>) {
    push @tests, $1 if ($line =~ /^TEST\(([^)]+)\)/);
}
close (FILE);

my $template = Template->new();
$template->process('test_template.c', {fixture => $fixture, tests => \@tests})
    || croak $template->error();

