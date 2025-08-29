#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *vstup = fopen("C:/Users/dulik/Downloads/text.txt", "r");
    int kapacita = 50000000;
    char **slova = (char **) malloc(kapacita * sizeof(char *));
    int *cetnost = (int *) malloc(kapacita * sizeof(int *));
    int *soucty = (int *) malloc(kapacita * sizeof(int *)); // pro hledani anagramu

    int slovacount = 0;
    char slovo[10000];
    printf("%s\n", slovo);
    while (fscanf(vstup, "%s", slovo) != EOF) {
        int i, soucet = 0;
        for (i = 0; slovo[i] != 0; i++) {
            //odstraneni interpunkce
            soucet += slovo[i];
            if (ispunct(slovo[i])) {
                slovo[i] = 0;
                break;
            }
        }
        for (i = 0; i < slovacount; i++) {
            if (strcasecmp(slovo, slova[i]) == 0) {
                cetnost[i]++;
                soucty[i] = soucet;
                break;
            }
        }
        if (i == slovacount) {
            //toto slovo neni jeste v databazi
            char *uk = (char *) malloc(strlen(slovo) + 1);
            slova[i] = uk;
            strcpy(slova[i], slovo);
            cetnost[i] = 1;
            soucty[i] = soucet;
            slovacount++;
            if (slovacount == kapacita) {
                printf("Koncime,slovacount=%d\n", slovacount);
                return 0;
                break;
            }
        }
    }
    for (int i = 0; i < slovacount; i++) {
        for (int j = 0; j < slovacount - i; j++) {
            if (cetnost[j] < cetnost[j + 1]) {
                int temp = cetnost[j];
                cetnost[j] = cetnost[j + 1];
                cetnost[j + 1] = temp;
                temp = soucty[j];
                soucty[j] = soucty[j + 1];
                soucty[j + 1] = temp;

                char *temp2 = slova[j];
                slova[j] = slova[j + 1];
                slova[j + 1] = temp2;
            }
        }
    }

    for (int i = 0; i < slovacount; i++) {
        printf("%s;%d;%d\n", slova[i], cetnost[i], soucty[i]);
    }
    printf("%s\n", slovo);
}
