#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *vstup = fopen("C:/Users/dulik/Downloads/jmena.csv", "r");
    if (vstup == NULL) {
        printf("Error in opening file\n");
        return -1;
    }
    char str[1000];
    char jmeno[1000] = "ABDUL";
    printf("Zadej prijmeni\n");
    scanf("%999s", jmeno);
    int pocetlidi;
    int pocet = 0;
    while (fgets(str, 1000, vstup)) {
        //  printf("%s",str);
        pocet++;
        int rocnik = 1898;
        if (strstr(str, jmeno) != NULL) {
            printf("%s", str);
            for (int i = 0; str[i] != 0; i++) {
                if (str[i] == ';') {
                    sscanf(&str[i + 1], "%i", &pocetlidi);
                    if (pocetlidi > 0) {
                        printf("rocnik = %i, pocetlidi=%i\n", rocnik, pocetlidi);
                    }
                    rocnik++;
                }
            }
        }
    }
    printf("Number of lines = %d\n", pocet);
}
