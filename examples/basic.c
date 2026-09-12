#include "../TriesWithFrequencies.h"
#include <stdio.h>

static int show(const char *const *tokens, size_t n, double frequency, void *unused) {
    size_t i; (void)unused;
    printf("  ");
    for (i = 0; i < n; ++i) printf("%s%s", i ? "" : "", tokens[i]);
    printf(" (terminal frequency %.0f)\n", frequency);
    return 0;
}

int main(void) {
    static const char *arm[] = {"a", "r", "m"};
    static const char *arms[] = {"a", "r", "m", "s"};
    static const char *arc[] = {"a", "r", "c"};
    static const char *bar[] = {"b", "a", "r"};
    TWFWord words[] = {{arm,3}, {arms,4}, {arc,3}, {bar,3}};
    TWFNode *trie = twf_create(words, sizeof words / sizeof *words);
    TWFNode *probabilities = twf_node_probabilities(trie);

    if (!trie || !probabilities) return 1;
    puts("Trie as JSON:"); twf_print(trie, stdout);
    printf("contains 'arm': %s\n", twf_contains(trie, arm, 3) ? "yes" : "no");
    puts("Words:"); twf_visit_words(trie, show, NULL);
    puts("Node probabilities as JSON:"); twf_print(probabilities, stdout);
    twf_free(probabilities); twf_free(trie);
    return 0;
}
