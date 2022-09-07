use strict;
use warnings FATAL => 'all';

while (<>) {
    s/\b(\w)(\w)(.*?)\b/$2$1$3/g;
    print;
}
