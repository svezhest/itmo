use strict;
use warnings FATAL => 'all';

while (<>) {
    s/(\w)(\1)+/{$1}/eg;
    print;
}
