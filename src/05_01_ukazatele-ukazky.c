#include <stdio.h>
#include <stdlib.h>

// char ret[250000000]="Ahoj svete"; // FUJ!!! Vytvoří EXE soubor 250 MB velký

char * usekniOdradkovani(char ret[]) { //ukazka pouziti ukazatelu pro vraceni poli
    for (int i=0; ret[i] != 0; i++) {
        if (ret[i]=='\n') {
            ret[i]=0;
            break;
        }
    }
    return ret;
}

int * generujPoleIntegeru(int pocet) {  //2. ukazka pouziti ukazatelu pro vraceni poli
    int * uk =  malloc(pocet * sizeof (int));
    for (int i=0; i<pocet; i++) {
        uk[i] = rand(); // rand() generuje nahodna cisla integer
    }
    return uk;
}

int main() {
    char ahoj[]="Ahoj svete\n";
    puts(usekniOdradkovani(ahoj));
    int * poleIntegeru=generujPoleIntegeru(10);
    
    char * uk=malloc(3000000);
    int * ukInt = malloc(1000 * sizeof (int));

    *uk='a';
    putchar(uk[0]); // *uk je to same jako uk[0]

    puts("\nNapiste na klavesnici retezec, konec=ENTER:");
    scanf("%s", uk);
    puts(uk);
    free(uk); // uvolneni - vraceni pameti operacnimu systemu
    *ukInt = 25;
    ukInt[0] = 25; // *ukInt je to same jako ukInt[0]
    puts("Napiste na klavesnici nekolik cisel integer, konec=retezec:");

    ukInt[10] = 2;
    *(ukInt+10)=2; //  *(uk+10) je to same jako ukInt[10]

    int *pomUk=ukInt;
    for (int i=0; i<1000; i++) {
        //scanf("%d", &ukInt[i]); // je to samé jako:
       int status = scanf("%d", pomUk++);
       if (status<1) {
           puts("Chyba vstupu = konec zadavni");
           break;
       }
    }
    int pocetPrvku=pomUk - ukInt - 1;
    for (int i=0; i<pocetPrvku; i++)
        printf("prvek c. %d = %d\n", i, ukInt[i]);

                //scanf("%d", &ukInt[0]); // &ukInt[0] je to same jako ukInt
    printf("Pocet zadanych prvku = %d\n", pomUk - ukInt - 1);

    free(ukInt);
    // free(pomUk); // bacha - chyba - spatna adresa, navic uvnitr uz uvolneneho bloku = PAD PROGRAMU!

    puts("OK, koncime");
    return 0;
}
