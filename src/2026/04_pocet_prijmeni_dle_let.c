#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* pro SetConsoleOutputCP(CP_UTF8) je potřeba:
#ifdef _WIN32
#include <windows.h>
#endif
*/
typedef struct {
    char prijmeni[100];
    int pocetProRokNarozeni[120];
} tZaznam;

int main(void) {
#ifdef _WIN32
    //SetConsoleOutputCP(CP_UTF8); // Ve Windows musíme konzolu nastavit na UTF8. Alternativa:
    system("chcp 65001 > nul");
    //test:
    //printf("Příliš žluťoučký kůň úpěl ďábelské ódy.\n");
#endif
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
        int delka=strlen(zaznamy[i].prijmeni);
        char * ret = line + delka+1;
        // printf("%s: ", zaznamy[i].prijmeni);
        for (int j=0; j<120; j++) {
            int pocet=0;
            char pocetRet[20];
            sscanf(ret, "%[^;];", pocetRet);
            pocet=atoi(pocetRet);
            if (pocet>0) {
            //    printf("%d: %d, ", 1899+j, pocet);
            }
            int d=strlen(pocetRet);
            ret=ret + d+1;
            zaznamy[i].pocetProRokNarozeni[j]=pocet;
            if (ret[0]==0 || isspace(ret[0])) break;
        }
        i++;
    }
    int pocet=i;
    char hledanePrijmeni[200];
    printf("Ktere prijmeni vas zajima?");
    while (scanf("%s", hledanePrijmeni) != EOF) {
        for (int i=0; i<pocet; i++) {
            if (strstr(zaznamy[i].prijmeni, hledanePrijmeni) != NULL) {
                printf("\n%s:==================\n", zaznamy[i].prijmeni);
                for (int j=0; j<120; j++) {
                    if (zaznamy[i].pocetProRokNarozeni[j]>0)
                        printf("%d: %d, ", 1898+j, zaznamy[i].pocetProRokNarozeni[j]);
                }
            }
        }
        printf("\nKtere prijmeni vas zajima?");
    }
    return 0;
}
