#include <stdio.h>
#include <limits.h>
#include <math.h>

int main() {
    double porodnost;
    double populace;
    int pocet_generaci;
    int x;
    printf("zadejte velikost populace:");
    scanf_s("%lf", &populace);
    printf("zadejte porodnost:");
    scanf_s("%lf", &porodnost);
    printf("zadejte pocet generaci:");
    scanf_s("%d", &pocet_generaci);
    x = pocet_generaci;
    for (; pocet_generaci > 0; pocet_generaci--) {
        populace = populace * (porodnost / 2.0);
    }
    printf("populace po %d generacich bude: %lf\n", x, populace);
    return 0;
}
