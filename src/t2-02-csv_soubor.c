#include <stdio.h>
#include <stdlib.h>

int cleanBuffer(FILE *f) {
    char znak;
    int pocet=0;
    while ((znak = fgetc(f)) != '\n') {
        pocet++;
    };
    return pocet;
}


int main() {
    int a;
    int b;
    int c;
    double souceta = 0, soucetb = 0, soucetc = 0, pocet = 0;
    char   jmeno[500];
    FILE * f = fopen("znamky.txt", "r");
    if (f == NULL) {
        puts("Error opening file, I will use standard input...");
        f=stdin;
    }
    printf("Zadej jmeno a tri cisla: ");
    while(1) {
        int status = fscanf(f,"%499[^,],%d,%d,%d", jmeno,&a,&b,&c);
        if(status == 4) {
            printf("jmeno = %s, a = %d, b = %d, c = %d, status = %d\n", jmeno,a,b,c, status);
            cleanBuffer(f); //smazani prebytecneho \n na konci radku vstupu
            souceta +=a;
            soucetb +=b;
            soucetc +=c;
            pocet++;
        }
        else if(status == EOF){
            break;
        }
        else {
            if(jmeno[0] == 'k') {
                break;
            }
            printf("Sorry mas to blbe, zkus to znovu.\n");
            cleanBuffer(f);
        }
    }
    printf("prumer a = %lf, prumer b = %lf, prumer c = %lf", souceta/pocet, soucetb/pocet, soucetc/pocet);
}
