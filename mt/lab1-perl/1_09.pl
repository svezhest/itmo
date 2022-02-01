use strict;
use warnings FATAL => 'all';
while (<>) {
    print if /^(?![^\n\S])/ && !/[^\n\S]$/;
}
