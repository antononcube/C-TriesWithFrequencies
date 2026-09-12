#include "../TriesWithFrequencies.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { size_t count; } Counter;
static int count_word(const char *const *tokens, size_t n, double value, void *ctx) {
    Counter *c = ctx;
    (void)tokens; (void)n; (void)value;
    ++c->count;
    return 0;
}

int main(void) {
    static const char *w1[] = {"b", "a", "r", "k"};
    static const char *w2[] = {"b", "a", "r", "k", "s"};
    static const char *w3[] = {"b", "a", "l", "m"};
    static const char *prefix[] = {"b", "a", "r", "k"};
    static const char *missing[] = {"b", "a", "z"};
    TWFWord words[] = {{w1,4},{w2,5},{w3,4}};
    TWFNode *trie = twf_create(words, 3), *copy, *prob, *shrunk, *pruned, *filtered;
    const TWFNode *node; const char **choice; size_t choice_len, total=0, internal=0, leaves=0;
    Counter counter={0}; unsigned int seed=7; char *json;

    assert(trie);
    assert(twf_is_key(trie, prefix, 4));
    assert(twf_contains(trie, prefix, 4));       /* bark is also a word */
    assert(!twf_contains(trie, missing, 3));
    assert(twf_position(trie, missing, 3) == 2);
    node = twf_retrieve(trie, prefix, 4);
    assert(node && node->value == 2.0);

    copy = twf_clone(trie); assert(copy && twf_equal(trie, copy));
    assert(twf_insert(copy, w1, 4, 1, 1));
    assert(!twf_equal(trie, copy));
    twf_free(copy);

    prob = twf_node_probabilities(trie);
    assert(prob && prob->value == 1.0);
    assert(fabs(prob->children->value - 1.0) < 1e-12);
    twf_free(prob);

    shrunk = twf_shrink(trie, ":", -1, false);
    assert(shrunk && twf_contains(shrunk, (const char *[]) {"b:a", "r:k"}, 2));
    twf_free(shrunk);
    pruned = twf_prune(trie, 2);
    assert(pruned && twf_is_key(pruned, (const char *[]) {"b", "a"}, 2));
    assert(!twf_is_key(pruned, prefix, 4));
    twf_free(pruned);

    filtered = twf_remove_by_threshold(trie, 2.0, true, "other");
    assert(filtered && filtered->children); twf_free(filtered);
    filtered = twf_remove_by_pareto_fraction(trie, .8, true, NULL);
    assert(filtered); twf_free(filtered);

    twf_node_counts(trie, &total, &internal, &leaves);
    assert(total == 8 && internal == 6 && leaves == 2);
    assert(twf_visit_words(trie, count_word, &counter) == 0 && counter.count == 3);
    assert(twf_random_choice(trie, true, &seed, &choice, &choice_len) == 0);
    assert(choice_len >= 4); twf_free_choice(choice);
    json = twf_to_json(trie, -1); assert(json && strstr(json, "\"key\":\"b\"")); free(json);
    twf_free(trie);
    puts("all TriesWithFrequencies tests passed");
    return 0;
}
