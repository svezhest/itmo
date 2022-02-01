use strict;
use warnings FATAL => 'all';
while (<>) {
    print if /[xyz][\w]{5,17}[xyz]/;
}

