#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int cleanBuffer(FILE *f) {
    char znak;
    int pocet = 0;
    while ((znak = fgetc(f)) != '\n') {
        pocet++;
    };
    return pocet;
}

double mojeStrtod(char ret[]) {
    char *ukerr;
    double a = strtod(ret, &ukerr);
    if (!(isspace(ukerr[0]) || ukerr[0] == 0))
        printf("CHYBA!!! ret = %s - ukerr = %s - znak = %d\n", ret, ukerr, ukerr[0]);
    return a;
}

void prohod(int *uka, int *ukb) {
    int tmp = *uka;
    printf("zacatek prohod(): a=%d, b=%d\n", *uka, *ukb);
    *uka = *ukb;
    *ukb = tmp;
    printf("konec prohod(): a=%d, b=%d\n", *uka, *ukb);
}

int main() {
    int x = 10, y = 20;
    prohod(&x, &y);
    printf("po navratu z prohod(): x=%d, y=%d\n", x, y);

    double a, b, c;

    double souceta = 0, soucetb = 0, soucetc = 0, pocet = 0;
    char jmeno[500];
    FILE *f = fopen("znamky.txt", "r");
    if (f == NULL) {
        puts("Error opening file, I will use standard input...");
        f = stdin;
    }
    printf("Zadej jmeno a tri cisla: ");
    while (1) {
        char radek[500];
        //int status = fscanf(f,"%499[^,],%lf,%lf,%lf", jmeno,&a,&b,&c);
        char *status = fgets(radek, 499, f);
        if (status == NULL)break;
        char vyska[500], vaha[500], vek[500];
        int status2 = sscanf(radek, "%499[^,],%499[^,],%499[^,],%499[^,]", jmeno, vyska, vaha, vek);
        if (status2 == 4) {
            char *ukerr;
            a = mojeStrtod(vyska);
            b = mojeStrtod(vaha);
            c = mojeStrtod(vek);
            printf("jmeno = %s, a = %lf, b = %lf, c = %lf, status = %d\n", jmeno, a, b, c, status2);

            souceta += a;
            soucetb += b;
            soucetc += c;
            pocet++;
        } else if (status == EOF) {
            break;
        } else {
            if (jmeno[0] == 'k') {
                break;
            }
            printf("Sorry mas to blbe, zkus to znovu.\n");
        }
    }
    printf("prumer a = %lf, prumer b = %lf, prumer c = %lf", souceta / pocet, soucetb / pocet, soucetc / pocet);
}
