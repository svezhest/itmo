use strict;
use warnings FATAL => 'all';

while (<>) {
    s/\b([\d]+)0\b/{$1}/eg;
    print;
}
