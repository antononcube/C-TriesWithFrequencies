#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
cc -std=c99 -Wall -Wextra -Werror -pedantic TriesWithFrequencies.c t/test_tries.c -o /tmp/twf-tests
/tmp/twf-tests
