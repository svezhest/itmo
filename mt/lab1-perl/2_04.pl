use strict;
use warnings FATAL => 'all';

while (<>) {
    s/^(\W*)(\w+)(\W+)(\w+)(.*)$/$1$4$3$2$5/;
    print;
}
