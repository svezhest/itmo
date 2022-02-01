use strict;
use warnings FATAL => 'all';
while (<>) {
    print if /z[\w]{3}z/;
}

