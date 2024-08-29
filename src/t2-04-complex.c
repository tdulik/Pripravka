#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cleanBuffer(FILE *f) {
    char znak;
    int pocet = 0;
    while ((znak = fgetc(f)) != '\n') {
        pocet++;
    };
    return pocet;
}

typedef struct {
    double real, imag;

} tComplex;

tComplex soucet(tComplex num1, tComplex num2) {
    tComplex vysledek = {num1.real + num2.real, num1.imag + num2.imag};
//    vysledek.real = num1.real + num2.real;
//    vysledek.imag = num1.imag + num2.imag;

    return vysledek;
};

tComplex nasobeni(tComplex num1, tComplex num2) {
    tComplex vysledek;

//    x⋅y=(x1y1−x2y2)+(x1y2+x2y1)i
    vysledek.real = num1.real * num2.real - num1.imag * num2.imag;
    vysledek.imag = num1.real * num2.imag + num1.imag * num2.real;

    return vysledek;
};

void tiskni(tComplex x) {
    printf("real = %lf, imag = %lf", x.real, x.imag);
}

void vloz(tComplex *uk) {
    puts("Vloz realnou a imaginarni cast komplexniho cisla: ");
    int status = scanf("%lf%lf", &(*uk).real, &uk->imag);
    if (status < 2) {
        puts("Chyba pri zadavani.");
        cleanBuffer(stdin);
    }
}

int main(int argc, char *argv[]) {
    tComplex prom1 = {12, 21};
    tComplex prom2 = {43, 10};
    vloz(&prom1);
    vloz(&prom2);
    puts("Vysledek nasobeni:");
    tiskni(nasobeni(prom1, prom2));
}
