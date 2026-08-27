#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
#define MAX_WORDS 600000
typedef struct {
    char word[MAX_LEN];
    unsigned long long int hash;
    char sorted[MAX_LEN];
    bool done;
} tAnagram;
int compareCharacters(const void *p1, const void *p2) {
    const char *uk1 = (char *) p1, *uk2 = (char *) p2;
    return *uk1 - *uk2;
};
int fget_words(FILE *vstup, tAnagram *anagram) {
    int c, i = 0;
    unsigned long long int soucet = 0, soucin = 1;
    while ((c = fgetc(vstup)) != EOF && c != '\n' && i < MAX_LEN) {
        if (isalpha(c)) {
            c = tolower(c);
            anagram->word[i] = anagram->sorted[i] = c;
            i++;
            char val = c - 'a' + 1;
            if (val < 0) val = 0;
            soucin = soucin * val;
            soucet = soucet + val;
        }
    }
    anagram->word[i] = anagram->sorted[i] = 0;
    anagram->hash = soucet + soucin;
    anagram->done = false;
    qsort(anagram->sorted, i, 1, compareCharacters);
    return c;
}
int main(void) {
    printf("Hledani anagramu...\n");
    FILE *vstup = fopen("czech_words.txt", "r");
    if (vstup == NULL) {
        printf("Nelze otevrit text.txt\n");
        return 1;
    }
    static tAnagram anagrams[MAX_WORDS];
    int i = 0;
    while (fget_words(vstup, &anagrams[i]) != EOF && i<MAX_WORDS) {
        i++;
    }
    int pocet = i, pocetSkupin = 0, pocetAnagramu = 0;
    for (i = 0; i < pocet; i++) {
        if (anagrams[i].done) continue;
        unsigned long long int hash = anagrams[i].hash;
        bool first = true;
        for (int j = i + 1; j < pocet; j++) {
            if (anagrams[j].hash == hash &&
                strcmp(anagrams[i].word, anagrams[j].word) != 0 &&
                strcmp(anagrams[j].sorted, anagrams[i].sorted) == 0) {
                if (first) {
                    pocetSkupin++;
                    printf("Anagramy se slovem %s (hash=%llu, sorted=%s):\n",
                           anagrams[i].word, hash, anagrams[i].sorted);
                    first = false;
                }
                printf("    %s, %llu, %s\n", anagrams[j].word, anagrams[j].hash,
                       anagrams[j].sorted);
                anagrams[j].done = true;
                pocetAnagramu++;
            }
        }
        if (!first && pocetSkupin % 100 == 0)
            fprintf(stderr, "Zpracovano: %d. slovo z %d, pocet skupin=%d, pocet anagramu celkem=%d\n",
                    i, pocet, pocetSkupin, pocetAnagramu);
    }
    printf("Pocet skupin=%d, pocet anagramu celkem=%d\n", pocetSkupin, pocetAnagramu);
    return 0;
}
