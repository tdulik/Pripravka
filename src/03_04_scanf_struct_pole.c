#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char jmeno[80];
    int znamky[10];
    double minuly_prumer;
} tStudent;

int main() {
    tStudent franta={"Franta Dobrota", {1,2,1,1,}};
    puts(franta.jmeno); // = printf("%s\n", franta.jmeno);
    printf("Frantovi znamky: %d, %d, %d\n",
           franta.znamky[0], franta.znamky[1], franta.znamky[2]);
    tStudent studenti[100]; //databaze 100 studentu
    puts("Zadejte jmeno a 3 znamky pro kazdeho studenta (cela cisla) a ENTER:");
    int status, i=0;
    do {
        status = scanf("%s%d%d%d",
                       studenti[i].jmeno, &studenti[i].znamky[0],
                       &studenti[i].znamky[1], &studenti[i].znamky[2]);
        if (status == 4) {
            puts("OK");
            i++;
        } else if (status!=EOF) { // v pripade chybneho vstupu:
            printf("Chyba ve vstupu, preskakuji radek.\n");
            int znak;
            while ( (znak=getchar()) != EOF && znak!='\n') { // lze i gets_s() nebo fgets()
            };
        }
    } while (status != EOF); //EOF je end of file
    printf("Spravne nacteno %d radku\n", i);

}

