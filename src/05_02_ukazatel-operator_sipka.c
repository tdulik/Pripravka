#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char jmeno[80];
    int znamky[10];
    double minuly_prumer;
} tStudent;

int main() {
    tStudent * uk = malloc(100 * sizeof (tStudent));
    uk[0].minuly_prumer = 1; // je stejne jako:
    (*uk).minuly_prumer=1;  // je stejne jako:
    uk->minuly_prumer = 1; // ale tohle je nejkratsi zapis
    uk++;
    uk->minuly_prumer = 1; // Zapis dalsiho studenta, typicky ve smycce

    puts("Zadej jmeno studenta: ");
    scanf("%s", uk[0].jmeno);
    printf("Jmeno=%s\n", uk[0].jmeno);

    return 0;
}