#include <stdio.h>
#include <stdbool.h>

int main() {
    int znamky[100][10]; //100 studentu, 10 predmetu
    puts("Zadejte 3 znamky pro kazdeho studenta (cela cisla) a ENTER:");
    int status, i=0;
    do {
        status = scanf("%d%d%d",
                       &znamky[i][0], &znamky[i][1], &znamky[i][2]);
        if (status == 3) {
            printf("status=%d, 1.znamka=%d, 2.znamka=%d, 3.znamka=%d\n",
                   status, znamky[i][0], znamky[i][1], znamky[i][2]);
        } else if (status!=EOF) { // v pripade chybneho vstupu:
            printf("Chyba ve vstupu, preskakuji radek.\n");
            int znak;
            while ( (znak=getchar()) != EOF && znak!='\n') { // lze i gets_s() nebo fgets()
            };
        }
    } while (status != EOF); //EOF je end of file

}

