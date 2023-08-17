#include <stdio.h>
#include <math.h>

double obvodKruhu(double r) {
    return 2*M_PI*r;  //3.14159265358979323846
}

double pythagoras(double a, double b) {
    return sqrt(a*a + b*b);
}

double vypocet_populace(double populace, int pocet_generaci, double porodnost) {
    for (; pocet_generaci > 0; pocet_generaci--) {
        populace = populace * (porodnost / 2.0);
    }
    return populace;
}

void NEnulovani(int x, int y) {
    printf("x=%d, y=%d\n", x,y);
    x=y=0;
    printf("x=%d, y=%d\n", x,y);
}

void nulovani(int * x, int * y) {
    printf("x=%d, y=%d\n", *x,*y);
    *x=*y=0;
    printf("x=%d, y=%d\n", *x,*y);
}
int main() {
    double obvod= obvodKruhu(1.0);
    printf("Obvod kruhu pro r=1 je %lf\n", obvod);
    printf("Pythagoras pro a=3, b=4 je %lf\n", pythagoras(3,4));
    printf("Populace pro porodnost 1.8, 10mil obyv. po 5 generaci je %lf\n",
           vypocet_populace(10000000,5, 1.8));
    int a=10, b=100;
    NEnulovani(a, b);
    printf("a=%d, b=%d\n", a,b);
    nulovani(&a, &b);
    printf("a=%d, b=%d\n", a,b);
    return 0;
}