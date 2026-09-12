#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
cc -std=c99 -Wall -Wextra TriesWithFrequencies.c examples/basic.c -o /tmp/twf-basic
/tmp/twf-basic
