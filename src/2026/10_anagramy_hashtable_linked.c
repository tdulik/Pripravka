#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LEN 100
#define HASH_TABLE_SIZE 1000003
#define PRINT_ANAGRAMS 1
typedef struct tWord {
    char word[MAX_LEN];
    struct tWord *next;
} tWord;
typedef struct tGroup {
    unsigned long long int hash;
    char sorted[MAX_LEN];
    int count;
    /*
     * Seznam skutečných anagramů v této skupině.
     */
    tWord *words;
    /*
     * Další tGroup ve stejném bucketu.
     * Toto je řetězení kolizí hash tabulky.
     */
    struct tGroup *next;
} tGroup;
/*
 * Pouze dočasná struktura pro právě načtené slovo.
 * Po vložení do hash tabulky může být znovu použita.
 */
typedef struct {
    char word[MAX_LEN];
    unsigned long long int hash;
    char sorted[MAX_LEN];
} tAnagram;
int compareCharacters(const void *p1, const void *p2) {
    const char *uk1 = (const char *) p1;
    const char *uk2 = (const char *) p2;
    return *uk1 - *uk2;
}
int fget_words(FILE *vstup, tAnagram *anagram) {
    int c, i = 0;
    unsigned long long int soucet = 0, soucin = 1;
    while ((c = fgetc(vstup)) != EOF && c != '\n') {
        if (isalpha((unsigned char) c) && i < MAX_LEN - 1) {
            c = tolower((unsigned char) c);
            anagram->word[i] = anagram->sorted[i] = (char) c;
            i++;
            char val = (char) (c - 'a' + 1);
            if (val < 0)
                val = 0;
            soucin = soucin * val;
            soucet = soucet + val;
        }
    }
    anagram->word[i] = anagram->sorted[i] = 0;
    anagram->hash = soucet + soucin;
    qsort(anagram->sorted, i, sizeof(char), compareCharacters);
    return c;
}
/*
 * Zkontroluje, zda už přesně stejné slovo
 * v anagramové skupině není.
 */
bool same_word_in_group(const tGroup *group, const char *word) {
    for (const tWord *p = group->words; p != NULL; p = p->next) {
        if (strcmp(p->word, word) == 0)
            return true;
    }
    return false;
}
bool insert_word(tGroup *hashTable[], const tAnagram *anagram, int *pocetSkupin,
                 int *pocetAnagramu) {
    int bucket = (int) (anagram->hash % HASH_TABLE_SIZE);
    /*
     * Nejprve hledáme, zda skupina už existuje.
     */
    for (tGroup *group = hashTable[bucket]; group != NULL; group = group->next) {
        /*
         * Stejný bucket ještě nestačí.
         *
         * Nejprve kontrolujeme celý hash,
         * potom definitivně sorted.
         */
        if (group->hash == anagram->hash && strcmp(group->sorted, anagram->sorted) == 0) {
            /*
             * Přesně stejné slovo podruhé
             * nepřidáváme.
             */
            if (same_word_in_group(group, anagram->word))
                return true;
            tWord *word = malloc(sizeof(tWord));
            if (word == NULL)
                return false;
            strcpy(word->word, anagram->word);
            word->next = group->words;
            group->words = word;
            /*
             * Pokud měla skupina před vložením
             * právě jedno slovo, právě teď se
             * stala anagramovou skupinou.
             */
            if (group->count == 1)
                (*pocetSkupin)++;
            group->count++;
            /*
             * Původní program počítal do
             * pocetAnagramu všechny členy
             * skupiny kromě prvního.
             */
            (*pocetAnagramu)++;
            return true;
        }
    }
    /*
     * Skupina zatím neexistuje.
     * Vytvoříme tGroup a její první tWord.
     */
    tGroup *group = malloc(sizeof(tGroup));
    tWord *word = malloc(sizeof(tWord));
    if (group == NULL || word == NULL) {
        free(group);
        free(word);
        return false;
    }
    group->hash = anagram->hash;
    strcpy(group->sorted, anagram->sorted);
    group->count = 1;
    strcpy(word->word, anagram->word);
    word->next = NULL;
    group->words = word;
    /*
     * Novou skupinu vložíme na začátek
     * seznamu daného bucketu.
     */
    group->next = hashTable[bucket];
    hashTable[bucket] = group;
    return true;
}
void print_groups(tGroup *hashTable[]) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        for (tGroup *group = hashTable[i]; group != NULL; group = group->next) {
            if (group->count <= 1)
                continue;
            printf("Anagramy "
                   "(hash=%llu, sorted=%s):\n",
                   group->hash, group->sorted);
            for (tWord *word = group->words; word != NULL; word = word->next) {
                printf("    %s\n", word->word);
            }
        }
    }
}
void free_hash_table(tGroup *hashTable[]) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        tGroup *group = hashTable[i];
        while (group != NULL) {
            tGroup *nextGroup = group->next;
            tWord *word = group->words;
            while (word != NULL) {
                tWord *nextWord = word->next;
                free(word);
                word = nextWord;
            }
            free(group);
            group = nextGroup;
        }
    }
}
int main(void) {
    printf("Hledani anagramu...\n");
    FILE *vstup = fopen("czech_words.txt", "r");
    if (vstup == NULL) {
        printf("Nelze otevrit czech_words.txt\n");
        return 1;
    }
    /*
     * Hash tabulka ukazatelů na první tGroup
     * v každém bucketu.
     *
     * static => inicializace NULL.
     */
    static tGroup *hashTable[HASH_TABLE_SIZE];
    /*
     * Potřebujeme pouze jeden dočasný objekt.
     */
    tAnagram anagram;
    int pocetSlov = 0;
    int pocetSkupin = 0;
    int pocetAnagramu = 0;
    clock_t start = clock();
    while (true) {
        int c = fget_words(vstup, &anagram);
        if (c == EOF && anagram.word[0] == 0)
            break;
        /*
         * Slovo okamžitě zařadíme
         * do příslušné skupiny.
         */
        if (!insert_word(hashTable, &anagram, &pocetSkupin, &pocetAnagramu)) {
            fprintf(stderr, "Nedostatek pameti.\n");
            fclose(vstup);
            free_hash_table(hashTable);
            return 1;
        }
        pocetSlov++;
        if (c == EOF)
            break;
    }
    fclose(vstup);
    /*
     * V tomto okamžiku už jsou všechny
     * anagramové skupiny hotové.
     */
    clock_t end = clock();
    printf("Pocet slov=%d, "
           "pocet skupin=%d, "
           "pocet anagramu celkem=%d\n",
           pocetSlov, pocetSkupin, pocetAnagramu);
    printf("Nacteni + seskupeni: %.3f s\n", (double) (end - start) / CLOCKS_PER_SEC);
    printf("Celkem bez vypisu:   %.3f s\n", (double) (end - start) / CLOCKS_PER_SEC);
#if PRINT_ANAGRAMS
    /*
     * Výpis probíhá až po skončení měření.
     */
    print_groups(hashTable);
#endif
    /*
     * Ani uvolňování paměti není
     * zahrnuto do měřeného času.
     */
    free_hash_table(hashTable);
    return 0;
}
