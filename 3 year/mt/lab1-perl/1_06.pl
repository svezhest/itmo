use strict;
use warnings FATAL => 'all';
while (<>) {
    print if grep /^\d+$/, split /[^\w]+/;
}
