#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char jmeno[200];
    char znamky[20]; // 'A'-'F', 1..5
    double prumer_studia;
} tStudent;

int porovnej(const void * uk1, const void * uk2) {
    const tStudent * ukS1 = uk1, * ukS2 = uk2;
    //return (ukS1->prumer_studia - ukS2->prumer_studia) * 10;
    return strcmp(ukS1->jmeno, ukS2->jmeno);
}

int cleanBuffer(FILE *f) {
    char znak;
    int pocet=0;
    while ((znak = fgetc(f)) != '\n' && znak!=EOF) {
        pocet++;
    };
    return pocet;
}
int main(int argc, char *argv[]) {

    tStudent studenti[1000];

    FILE * f = fopen("znamky.txt", "r");
    if (f == NULL) {
        puts("Error opening file, I will use standard input...\n"
             "Zadej jmeno a tri cisla:");
        f=stdin;
    }
    int i=0;
    while(1) {
        int status = fscanf(f,"%199[^,],%d,%d,%d,%d,%d,%lf",
                            studenti[i].jmeno, studenti[i].znamky,studenti[i].znamky+1,
                            studenti[i].znamky+2,studenti[i].znamky+3,studenti[i].znamky+4,
                            &studenti[i].prumer_studia);

        if(status == 7) {
            puts("ok"); i++;
            cleanBuffer(f);

        }
        else if(status == EOF){
            puts("Konec souboru");
            break;
        }
        else{
            cleanBuffer(f);
            printf("Mas tam chybu status = %d\n", status);
        }
    }
    printf("i = %d\n", i);
    qsort(studenti, i, sizeof (tStudent), porovnej);
    for (int j = 0; j < i; ++j) {
        printf("%s, %d, %d, %d, %d, %d, %lf\n", studenti[j].jmeno,
               studenti[j].znamky[0],studenti[j].znamky[1],studenti[j].znamky[2],
               studenti[j].znamky[3],studenti[j].znamky[4],studenti[j].prumer_studia);
    }
}
