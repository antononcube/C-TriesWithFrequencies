# C-TriesWithFrequencies
C implementation of tries (prefix trees) with cumulative frequencies.

`TriesWithFrequencies.h` exposes a small C99 API. Keys are UTF-8 byte strings
and a word is an array of token strings, so the trie works equally well with
characters, syllables, or words. Every node's value is the cumulative frequency
of all words passing through it; a word ends at a node when its value exceeds
the sum of its child values. This matches the Java implementation's behavior.

Build and run the example:

```shell
sh examples/run-basic.sh
```

Run the tests:

```shell
sh t/run-tests.sh
```

The library has no dependencies beyond the C standard library. Returned tries,
JSON strings, and random-choice token arrays have explicit ownership documented
in the header.
