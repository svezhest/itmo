use strict;
use warnings FATAL => 'all';

while (<>) {
    print if (grep /\b(.+)\1\b/, split);
}
