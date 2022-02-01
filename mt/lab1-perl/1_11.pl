use strict;
use warnings FATAL => 'all';
use Math::BigInt;

while (<>) {
    print if /\b([0|1]+)\b/ && Math::BigInt->new("0b$1")->bmod(Math::BigInt->new("3"))  == Math::BigInt->new("0");
}
