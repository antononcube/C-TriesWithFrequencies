#include "../TriesWithFrequencies.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} Words;

static void free_words(Words *words) {
    size_t i;
    for (i = 0; i < words->count; ++i) free(words->items[i]);
    free(words->items);
}

static int add_word(Words *words, char *word) {
    char **items;
    size_t capacity;
    if (words->count == words->capacity) {
        capacity = words->capacity ? words->capacity * 2 : 1024;
        items = realloc(words->items, capacity * sizeof(*items));
        if (!items) return 0;
        words->items = items;
        words->capacity = capacity;
    }
    words->items[words->count++] = word;
    return 1;
}

/* Read newline-delimited words without relying on a non-C99 getline(). */
static int read_words(const char *path, Words *words) {
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t length = 0, capacity = 0;
    int ch;
    if (!file) return 0;
    while ((ch = fgetc(file)) != EOF) {
        char *grown;
        if (ch == '\n') {
            if (length) {
                line[length] = '\0';
                if (!add_word(words, line)) goto failure;
                line = NULL; length = capacity = 0;
            }
            continue;
        }
        if (ch == '\r') continue;
        if (length + 1 >= capacity) {
            capacity = capacity ? capacity * 2 : 64;
            grown = realloc(line, capacity);
            if (!grown) goto failure;
            line = grown;
        }
        line[length++] = (char)ch;
    }
    if (length) {
        line[length] = '\0';
        if (!add_word(words, line)) goto failure;
        line = NULL;
    }
    free(line);
    fclose(file);
    return 1;

failure:
    free(line);
    fclose(file);
    return 0;
}

static double now_seconds(void) {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec / 1000000.0;
}

static void shuffle_prefix(size_t *indices, size_t count, size_t wanted) {
    size_t i;
    for (i = 0; i < wanted; ++i) {
        size_t j = i + (size_t)(rand() % (int)(count - i));
        size_t temporary = indices[i];
        indices[i] = indices[j];
        indices[j] = temporary;
    }
}

static int make_character_words(char *const *strings, size_t count,
                                TWFWord **out_words, char ***out_tokens) {
    TWFWord *words = calloc(count, sizeof(*words));
    char **tokens;
    size_t i, j, token_count = 0;
    if (!words) return 0;
    for (i = 0; i < count; ++i) token_count += strlen(strings[i]);
    tokens = malloc(token_count * sizeof(*tokens));
    if (!tokens) { free(words); return 0; }
    token_count = 0;
    for (i = 0; i < count; ++i) {
        size_t length = strlen(strings[i]);
        words[i].tokens = (const char *const *)(tokens + token_count);
        words[i].length = length;
        for (j = 0; j < length; ++j) {
            tokens[token_count] = malloc(2);
            if (!tokens[token_count]) {
                while (token_count) free(tokens[--token_count]);
                free(tokens); free(words); return 0;
            }
            tokens[token_count][0] = strings[i][j];
            tokens[token_count++][1] = '\0';
        }
    }
    *out_words = words;
    *out_tokens = tokens;
    return 1;
}

static void free_character_words(TWFWord *words, char **tokens, size_t count) {
    size_t i, token_count = 0;
    for (i = 0; i < count; ++i) token_count += words[i].length;
    for (i = 0; i < token_count; ++i) free(tokens[i]);
    free(tokens);
    free(words);
}

int main(int argc, char **argv) {
    const char *dictionary = argc > 1 ? argv[1] : "/usr/share/dict/words";
    const size_t sizes[] = {10, 100, 1000, 10000, 100000};
    Words all = {0};
    size_t *indices, i;

    if (!read_words(dictionary, &all)) {
        fprintf(stderr, "Cannot read dictionary: %s\n", dictionary);
        return 1;
    }
    if (!all.count) {
        fprintf(stderr, "Dictionary contains no non-empty words: %s\n", dictionary);
        free_words(&all);
        return 1;
    }
    indices = malloc(all.count * sizeof(*indices));
    if (!indices) { free_words(&all); return 1; }
    for (i = 0; i < all.count; ++i) indices[i] = i;

    printf("C trie creation profiling\n");
    printf("dictionary: %s\n", dictionary);
    printf("words: %zu\n", all.count);
    printf("sample words:");
    shuffle_prefix(indices, all.count, all.count < 12 ? all.count : 12);
    for (i = 0; i < all.count && i < 12; ++i)
        printf("%s%s", i ? ", " : " ", all.items[indices[i]]);
    putchar('\n');
    puts("============================================================");
    puts("Across word collection sizes");
    puts("============================================================");

    srand(12);
    for (i = 0; i < sizeof(sizes) / sizeof(*sizes); ++i) {
        size_t requested = sizes[i];
        size_t count = requested > all.count ? all.count : requested;
        char **selected = malloc(count * sizeof(*selected));
        TWFWord *words;
        char **tokens;
        TWFNode *trie;
        size_t total = 0, internal = 0, leaves = 0, j;
        double start;
        if (!selected) break;
        shuffle_prefix(indices, all.count, count);
        for (j = 0; j < count; ++j) selected[j] = all.items[indices[j]];
        if (!make_character_words(selected, count, &words, &tokens)) {
            free(selected); break;
        }
        printf("n = %zu\n", requested);
        start = now_seconds();
        trie = twf_create(words, count);
        printf("number of words = %zu, creation time: %.6f seconds\n",
               count, now_seconds() - start);
        if (!trie) {
            fputs("Trie creation failed\n", stderr);
            free_character_words(words, tokens, count); free(selected); break;
        }
        twf_node_counts(trie, &total, &internal, &leaves);
        printf("Trie statistics: total nodes = %zu, internal nodes = %zu, leaves = %zu\n",
               total, internal, leaves);
        twf_free(trie);
        free_character_words(words, tokens, count);
        free(selected);
    }
    free(indices);
    free_words(&all);
    return 0;
}
