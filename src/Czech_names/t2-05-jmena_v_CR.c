#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    short int rok;
    short int pocet;
} tRokPocet;

typedef struct {
    char *jmeno;
    short int pocetRoku;
    tRokPocet *tabulkaCetnosti;
} tJmenoRoky;

void vypisPolozky(tJmenoRoky *tabulka) {
    printf("Jmeno: %s\n", tabulka->jmeno);
    for (int i = 0; i < tabulka->pocetRoku; ++i) {
        printf("Rok: %d, Pocet lidi: %d\n", tabulka->tabulkaCetnosti[i].rok, tabulka->tabulkaCetnosti[i].pocet);
    }
}


int main(int argc, char *argv[]) {
    FILE *f = fopen("t2-05-jmena_v_CR.csv", "r");
    if (f == NULL) {
        puts("Error opening file, I will use standard input...");
        f = stdin;
    }

    tJmenoRoky *tabulkaJmen = malloc(sizeof(tJmenoRoky) * 4 * 65000 + 25000);
    int cisloRadku = 0;

    char ret[2048];
    while (fgets(ret, 2047, f) != NULL) {
        //puts(ret);
        char jmeno[256];
        sscanf(ret, "%[^;];", jmeno);
        //puts(jmeno);
        int delkaJmena = strlen(jmeno);
        char *uk = ret + delkaJmena + 1;
        char *end;
        int pocet = 0;
        tRokPocet pracovniPole[150];
        int i = 0;
        while (1) {

            long hodnota = strtol(uk, &end, 10);
            //printf("%d ", hodnota);
            uk = end + 1;
            if (hodnota != 0) {
                pracovniPole[i] = (tRokPocet) {1898 + pocet, hodnota};
                i++;
            }
            pocet++;
            if (*end == '\n') break;

        }
        tRokPocet *tabulkaCetnosti = malloc(i * sizeof(tRokPocet));
        for (int j = 0; j < i; ++j) {
            tabulkaCetnosti[j] = pracovniPole[j];
        }

        tabulkaJmen[cisloRadku].pocetRoku = i;

        tabulkaJmen[cisloRadku].jmeno = malloc(delkaJmena + 1);
        strcpy(tabulkaJmen[cisloRadku].jmeno, jmeno);
        tabulkaJmen[cisloRadku].tabulkaCetnosti = tabulkaCetnosti;
        cisloRadku++;
        vypisPolozky(tabulkaJmen + cisloRadku - 1);
        //printf("pocet = %d\n", pocet);
    }
    printf("Nacetl se %d radku\n", cisloRadku);

}
