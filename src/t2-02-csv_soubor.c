#include <stdio.h>
#include <stdlib.h>

int cleanBuffer() {
    char znak;
    int pocet=0;
    while ((znak = getchar()) != '\n') {
        pocet++;
    };
    return pocet;
}

int vlozeniCisel(int pole[]) {
    int pocet=0, i=0;
    while (1) {
        int status;
        while ((status = scanf("%d", &pole[i])) != 1){
          pocet=cleanBuffer();
          if (pocet==1) return i;
          printf("Promin ale error");
        }
      i++;

    }
}


int main() {
    int a;
    int b;
    int c;
    double souceta = 0, soucetb = 0, soucetc = 0, pocet = 0;
    char   jmeno[5];
    printf("Zadej jmeno a tri cisla: ");
    while(1) {
        int status = scanf("%4[^,],%d,%d,%d", jmeno,&a,&b,&c);
        if(status == 4) {
            printf("jmeno = %s, a = %d, b = %d, c = %d, status = %d\n", jmeno,a,b,c, status);
            cleanBuffer(); //smazani prebytecneho \n na konci radku vstupu
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
            cleanBuffer();
        }
    }
    printf("prumer a = %lf, prumer b = %lf, prumer c = %lf", souceta/pocet, soucetb/pocet, soucetc/pocet);
}
