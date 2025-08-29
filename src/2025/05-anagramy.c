#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int porovnejPismeno (const void *a, const void *b) {
    const char* uk1 = a;
    const char* uk2 = b;
    return *uk1 - *uk2;
}
int main(void) {
    FILE *vstup = fopen("C:/Users/dulik/Downloads/text.txt", "r");
    int kapacita = 50000000;
    char **slova = (char **) malloc(kapacita * sizeof(char *));
    int *cetnost = (int *) malloc(kapacita * sizeof(int *));
    char **slovaSerazena = (char **) malloc(kapacita * sizeof(char *));
    unsigned long *hashcodes = malloc(kapacita * sizeof(int *)); // pro hledani anagramu

    int slovacount = 0;
    unsigned char slovo[10000];
    printf("%s\n", slovo);
    while (fscanf(vstup, "%s", slovo) != EOF) {
        int i;
        unsigned long int soucet=0, soucin=1, hash = 0;
        for (i = 0; slovo[i] != 0; i++) {
            //odstraneni interpunkce

            if (ispunct(slovo[i])) {
                slovo[i] = 0;
                break;
            }
            soucet += slovo[i];
            soucin *= slovo[i];
        }
        hash=soucin+soucet;
        for (i = 0; i < slovacount; i++) {
            if (strcasecmp(slovo, slova[i]) == 0) {
                cetnost[i]++;
                hashcodes[i] = hash;
                break;
            }
        }
        if (i == slovacount) {
            int delka= strlen(slovo);
            //toto slovo neni jeste v databazi
            char *uk = (char *) malloc(delka + 1);
            slova[i] = uk;
            strcpy(slova[i], slovo);
            qsort(slovo, delka, sizeof(char), porovnejPismeno);
            char *uk2 = (char *) malloc(strlen(slovo) + 1);
            slovaSerazena[i] = uk2;
            strcpy(slovaSerazena[i], slovo);
            cetnost[i] = 1;
            hashcodes[i] = hash;
            slovacount++;
            if (slovacount == kapacita) {
                printf("Koncime,slovacount=%d\n", slovacount);
                return 0;
            }
        }
    }
    for (int i = 0; i < slovacount; i++) {
        for (int j = 0; j < slovacount - i; j++) {
            if ( hashcodes[j] < hashcodes[j + 1]) {
//            if (strcmp(slova[j], slova[j + 1]) < 0) {
                unsigned long temp = cetnost[j];
                cetnost[j] = cetnost[j + 1];
                cetnost[j + 1] = temp;
                temp = hashcodes[j];
                hashcodes[j] = hashcodes[j + 1];
                hashcodes[j + 1] = temp;

                char *temp2 = slova[j];
                slova[j] = slova[j + 1];
                slova[j + 1] = temp2;

                char *temp3 = slovaSerazena[j];
                slovaSerazena[j] = slovaSerazena[j + 1];
                slovaSerazena[j + 1] = temp3;
            }
        }
    }

    for (int i = 0; i < slovacount-1; i++) {
        if (strcmp(slovaSerazena[i], slovaSerazena[i + 1]) == 0) {
            printf("%s;%d;%lu;%s\n", slova[i], cetnost[i], hashcodes[i], slovaSerazena[i]);
            printf("%s;%d;%lu;%s\n\n", slova[i+1], cetnost[i+1], hashcodes[i+1], slovaSerazena[i+1]);
        }

    }
}
