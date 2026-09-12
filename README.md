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
```
# Trie as JSON:
# {"key":"","value":4,"children":[{"key":"a","value":3,"children":[{"key":"r","value":3,"children":[{"key":"m","value":2,"children":[{"key":"s","value":1,"children":[]}]},{"key":"c","value":1,"children":[]}]}]},{"key":"b","value":1,"children":[{"key":"a","value":1,"children":[{"key":"r","value":1,"children":[]}]}]}]}
# contains 'arm': yes
# Words:
#   arm (terminal frequency 1)
#   arms (terminal frequency 1)
#   arc (terminal frequency 1)
#   bar (terminal frequency 1)
# Node probabilities as JSON:
# {"key":"","value":1,"children":[{"key":"a","value":0.75,"children":[{"key":"r","value":1,"children":[{"key":"m","value":0.66666666666666663,"children":[{"key":"s","value":0.5,"children":[]}]},{"key":"c","value":0.33333333333333331,"children":[]}]}]},{"key":"b","value":0.25,"children":[{"key":"a","value":1,"children":[{"key":"r","value":1,"children":[]}]}]}]}
```

Run the tests:

```shell
sh t/run-tests.sh
```
```
# all TriesWithFrequencies tests passed
```

The library has no dependencies beyond the C standard library. Returned tries,
JSON strings, and random-choice token arrays have explicit ownership documented
in the header.
