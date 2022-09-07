use strict;
use warnings FATAL => 'all';

my $s = "";

while (<>) {
    s/^(?!\n)(\s)+//;
    s/ ( )+/ /g;
    s/(\s)*\n/\n/g;
    s/^[\s]*$/\n\n/;
    $s = $s . $_;
}

$s =~ s/<.*?>//g;
$s =~ s/&lt.*?&gt//g;
$s =~ s/^(\n)+//;
$s =~ s/(\n)+$//;
$s =~ s/\n\n(\n)+/\n\n/g;

print $s;

