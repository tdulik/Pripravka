#include <stdio.h>
#include <math.h>

int main() {
    double a;
    printf("Zadej koeficient a:");
    scanf("%lf",&a);
    double b;
    printf("Zadej koeficient b:");
    scanf("%lf",&b);
    double c;
    printf("Zadej hodnotu c:");
    scanf("%lf",&c);

    double D = b*b-(4 * a * c);
    double x;
    double x1;
    double x2;

    if (D<0){
        printf("Nema reseni v oboru realnych cisel");
    }
    else if (D==0){
        x = -b/(2*a);
        printf("Kvadraticka rovnice ma jedno reseni - x = %lf",x);
    }
    else{
        double sd=sqrt(D);
        x1 = (-b+sd)/(2*a);
        x2= (-b-sd)/(2*a);
        printf("Kvadraticka rovnice ma dve reseni - x1 = %lf a x2 = %lf", x1, x2);
    }
    
}