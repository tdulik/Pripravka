#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, const char * argv[] ) {
    const int DEFAULT_POCET=5;
    int pocetSlov = DEFAULT_POCET;
    if (argc>1)
        pocetSlov=atoi(argv[1]);
    int DEFAULT_POCET_SPECIAL=6;
    if (argc>2)
        DEFAULT_POCET_SPECIAL=atoi(argv[2]);
    const int DEFAULT_POCET_HESEL=10;

    printf("Generator hesel!\n");
    char * slovnik[] = {
        "Ahoj", "Cau", "Cus", "OK",
        "KO", "Mele", "Maso", "Ema", "Mama"
    };
    char specialni[] = "!?-=;:/+*()%";
    printf("sizeof(slovnik)=%d\n", sizeof(slovnik));
    int pocet = sizeof(slovnik) / sizeof(slovnik[0]);
    int pocetSpecial;
    srand(time(NULL));
    int delkaSpecialni = sizeof(specialni) / sizeof(specialni[0]) - 1;
    for (int j = 0; j < DEFAULT_POCET_HESEL; j++) {
        pocetSpecial=DEFAULT_POCET_SPECIAL;
        for (int i = 0; i < pocetSlov; i++) {
            int r = rand() % pocet;
            printf("%s", slovnik[r]);
            if (pocetSpecial-- > 0)
                printf("%c", specialni[rand() % delkaSpecialni]);
        }
        while (pocetSpecial-- > 0)
            printf("%c", specialni[rand() % delkaSpecialni]);
        printf("\n");
    }
    return 0;
}
