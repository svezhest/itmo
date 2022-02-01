use strict;
use warnings FATAL => 'all';
while (<>) {
    print if grep /^cat$/, split /[^\w]+/;
}
