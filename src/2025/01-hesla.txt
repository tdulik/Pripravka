#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    printf("Nepouzivej heslo s hodne stejnymi znaky");
    srand(time(NULL));
    char *slovnik[] = {
        "Kolo", "Mele", "Maso", "Pes", "Na", "By", "Ti", "My", "To", "Je", "Ne", "Si", "On", "Vy", "Pes", "Les", "Dum",
        "Den", "Kun", "Caj", "Kul", "Rok", "Hra", "Nos", "Tu", "He", "Ja", "Vy", "Mi", "Do", "Se", "Uz", "Ti", "Ho",
        "Lev", "Sit", "Mir", "Cas", "Had", "Vul", "Tma", "Mrk", "Kod", "Raj"
    };
    slovnik[0][0]='k';
    int pocetslov = 5;
    printf("Pocetslov: ");
    scanf("%i", &pocetslov);

    int n = 44; // sizeof(slovnik) / sizeof(char *);
    printf("%i\n", n);
    printf("%i\n", rand() % n);
    for (int ii = 0; ii < 10; ii++) {
        for (int i = 0; i < pocetslov; i++) {
            int cislo = rand() % n;
            printf("%s", slovnik[cislo]);
        }
        printf("\n");
    }

    printf("\n");
}
