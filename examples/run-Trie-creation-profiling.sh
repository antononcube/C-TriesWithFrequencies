#!/bin/sh
set -eu

cd "$(dirname "$0")/.."
dictionary=${1:-/usr/share/dict/words}
cc -std=c99 -O3 -Wall -Wextra TriesWithFrequencies.c \
  examples/Trie-creation-profiling.c -o /tmp/twf-trie-creation-profiling
/tmp/twf-trie-creation-profiling "$dictionary"
