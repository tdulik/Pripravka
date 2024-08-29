#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void prohod(int *uka, int *ukb) {
    int tmp = *uka; // uka[0]
    printf("zacatek prohod(): a=%d, b=%d\n", *uka, *ukb);
    *uka = *ukb;
    *ukb = tmp;
    printf("konec prohod(): a=%d, b=%d\n", *uka, *ukb);
}

void generujCisla(int pole[], int pocetPrvku) {
    for (int i = 0; i < pocetPrvku; ++i) {
        pole[i] = rand();
        printf("%d, ", pole[i]);
    }
}

void generujRetezec(char pole[], int pocetPrvku) {
    int i;
    for (i = 0; i < pocetPrvku; ++i) {
        pole[i] = rand() % 26 + 'a';
    }
    pole[i] = 0;
    puts(pole);
}

char *generujHeslo(int pocetZnaku) {
    int i;
    char *pole = malloc(pocetZnaku + 1);
    for (i = 0; i < pocetZnaku; ++i) {
        pole[i] = rand() % 26 + 'a';
    }
    pole[i] = 0;
    return pole;
}

int porovnej(char * str1, char * str2) {
    while (*str1!=0 && *str2!=0 && (*str1 == *str2)) {
        str1++; str2++;
    };
    return *str1-*str2;
}

int main(int argc, char *argv[]) {
    int pocetZnaku = 16;
    if (argc > 1) {
        pocetZnaku = atoi(argv[1]);

    }
    srand(time(NULL));
    //char pole[16];
    //generujRetezec(pole, 16);
    char *heslo = generujHeslo(8);
    puts(heslo);
    puts(heslo+4); // ukazky ukazatelove aritmetiky
    char * uk = heslo+4;
    puts(++uk);
    puts(++uk);
    free(heslo);
}
