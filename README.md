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

----

## References

### Articles

[AA1] Anton Antonov,
["Tries with frequencies for data mining"](https://mathematicaforprediction.wordpress.com/2013/12/06/tries-with-frequencies-for-data-mining/),
(2013),
[MathematicaForPrediction at WordPress](https://mathematicaforprediction.wordpress.com).

[AA2] Anton Antonov,
["Removal of sub-trees in tries"](https://mathematicaforprediction.wordpress.com/2014/10/12/removal-of-sub-trees-in-tries/),
(2013),
[MathematicaForPrediction at WordPress](https://mathematicaforprediction.wordpress.com).

[AA3] Anton Antonov,
["Tries with frequencies in Java"](https://mathematicaforprediction.wordpress.com/2017/01/31/tries-with-frequencies-in-java/)
(2017),
[MathematicaForPrediction at WordPress](https://mathematicaforprediction.wordpress.com).
[GitHub Markdown](https://github.com/antononcube/MathematicaForPrediction).


[WK1] Wikipedia entry, [Trie](https://en.wikipedia.org/wiki/Trie).

### Packages

[AAp1] Anton Antonov,
[Tries with frequencies, Mathematica Version 9.0 package](https://github.com/antononcube/MathematicaForPrediction/blob/master/TriesWithFrequenciesV9.m),
(2013),
[MathematicaForPrediction at GitHub](https://github.com/antononcube/MathematicaForPrediction).

[AAp2] Anton Antonov,
[Tries with frequencies, Mathematica package](https://github.com/antononcube/MathematicaForPrediction/blob/master/TriesWithFrequencies.m),
(2013-2018),
[MathematicaForPrediction at GitHub](https://github.com/antononcube/MathematicaForPrediction).

[AAp3] Anton Antonov,
[Tries with frequencies in Java](https://github.com/antononcube/MathematicaForPrediction/tree/master/Java/TriesWithFrequencies),
(2017),
[MathematicaForPrediction at GitHub](https://github.com/antononcube/MathematicaForPrediction).

[AAp4] Anton Antonov,
[Java tries with frequencies, Mathematica package](https://github.com/antononcube/MathematicaForPrediction/blob/master/JavaTriesWithFrequencies.m),
(2017),
[MathematicaForPrediction at GitHub](https://github.com/antononcube/MathematicaForPrediction).

[AAp5] Anton Antonov,
[Java tries with frequencies, Mathematica unit tests](https://github.com/antononcube/MathematicaForPrediction/blob/master/UnitTests/JavaTriesWithFrequencies-Unit-Tests.wlt),
(2017),
[MathematicaForPrediction at GitHub](https://github.com/antononcube/MathematicaForPrediction).

[AAp6] Anton Antonov,
[TriesWithFrequencies, Java package](https://github.com/antononcube/Raku-Java-TriesWithFrequencies),
(2021-2023),
[GitHub/antononcube](https://github.com/antononcube).

[AAp7] Anton Antonov,
[ML::TriesWithFrequencies, Raku package](https://github.com/antononcube/Raku-ML-TriesWithFrequencies),
(2021),
[GitHub/antononcube](https://github.com/antononcube).

[AAp8] Anton Antonov,
[TriesWithFrequencies, Wolfram Language paclet](https://resources.wolframcloud.com/PacletRepository/resources/AntonAntonov/TriesWithFrequencies/),
(2023),
[Wolfram Language Paclet Repository](https://resources.wolframcloud.com/PacletRepository).

[AAp9] Anton Antonov,
[JavaTriesWithFrequencies, Wolfram Language paclet](https://resources.wolframcloud.com/PacletRepository/resources/AntonAntonov/JavaTriesWithFrequencies/),
(2023),
[Wolfram Language Paclet Repository](https://resources.wolframcloud.com/PacletRepository).

### Videos

[AAv1] Anton Antonov,
["Prefix Trees with Frequencies for Data Analysis and Machine Learning"](https://www.youtube.com/watch?v=MdVp7t8xQbQ),
(2017),
Wolfram Technology Conference 2017,
[Wolfram channel at YouTube](https://www.youtube.com/channel/UCJekgf6k62CQHdENWf2NgAQ).