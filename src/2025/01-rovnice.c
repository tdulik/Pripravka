#include <stdio.h>
#include <stdbool.h>
int main(void) {
    fprintf(stderr, "Vloz start x \n");
    int startx;
    int status=scanf("%d", &startx);
    if(status<1) {
        printf("Incorrect input for startx\n");
        return 1;
    }
    fprintf(stderr, "Vloz end x \n");
    int endx;
    status=scanf("%d", &endx);
    if(status<1) {
        printf("Incorrect input for endx\n");
        return 1;
    }
    fprintf(stderr, "Vloz parametry a, b:\n");
    double a;
    status=scanf("%lf", &a);
    if (status<1) {
        printf("Incorrect input for a\n");
        return 1;
    }
    double b;
    status=scanf("%lf", &b);
    if (status<1) {
        printf("Incorrect input for b\n");
        return 1;
    }
    FILE * vystup=fopen("Vystup.csv","w");
    if (vystup==NULL) {
        printf("Nelze otevrit soubor, koncime.");
        return 1;
    }
    //printf("a=%f, b=%f\n", a, b);
    double x,y;
    for (x=startx; x<=endx; x++) {
        y=-a*x/b;
        fprintf(vystup, "%f; %f\n", x, y);
    }

    return 0;
}
