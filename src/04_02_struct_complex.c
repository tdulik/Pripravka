#include <stdio.h>
#include <math.h>
typedef struct {
    double re, im;
} tComplex;
void tisk(tComplex c) {
    printf("re=%lf, im=%lf\n", c.re, c.im );
}
tComplex soucet(tComplex c1, tComplex c2) {
    tComplex vysledek; //={ c1.re+c2.re, c1.im + c2.im}; //tj. zkraceny zapis tohoto:
    vysledek.re = c1.re + c2.re;
    vysledek.im = c1.im + c2.im;
    return vysledek;
}

tComplex nasobek(tComplex c1, tComplex c2) {
    tComplex vysledek;
    //doplnte svuj kod
    return vysledek;
}


int main() {
    tComplex x1={1.0, 2.0}, x2={3,4};
    tisk(soucet(x1,x2));
    tisk(nasobek(x1,x2));

    return 0;
}