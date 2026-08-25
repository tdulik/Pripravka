#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char prijmeni[100];
    int pocetProRokNarozeni[120];
} tZaznam;

int main(void) {
    printf("Pocet prijmeni narozenych v danem roce:\n");
    FILE * vstup = fopen("t2-05-jmena_v_CR.csv", "r");
    if (vstup == NULL) {
        printf("Vstupni soubor nelze otevrit\n");
        return 1;
    }
    static tZaznam zaznamy[1000000];
    char line[1000];
    int i=0;
    while (fgets(line, sizeof(line), vstup) != NULL) {

        sscanf(line, "%[^;];", zaznamy[i].prijmeni);
        printf("%s\n", zaznamy[i].prijmeni);
        int delka=strlen(zaznamy[i].prijmeni);
        char * ret = line + delka+1;
        //printf("%s\n", ret);
        for (int j=0; j<120; j++) {
            int pocet=0;
            char pocetRet[20];
            sscanf(ret, "%[^;];", pocetRet);
            pocet=atoi(pocetRet);
            int d=strlen(pocetRet);
            ret=ret + d+1;
            zaznamy[i].pocetProRokNarozeni[j]=pocet;
            if (ret[0]=0 || isspace(ret[0])) break;
        }
        i++;
    }
    return 0;
}
