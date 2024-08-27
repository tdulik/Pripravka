#include <stdio.h>
#include <stdlib.h>

int cleanBuffer() {
    char znak;
    int pocet=0;
    while ((znak = getchar()) != '\n') {
        pocet++;
    };
    return pocet;
}

int porovnejPoleCisel(int pole1[], int pole2[], int n) {
    for (int i = 0; i < n; ++i) {
        if(pole1[i] < pole2[i]){
            puts("Pole 1 je mensi");
            return 0;
        }
        else if(pole1[i] > pole2[i]){
            puts("Pole 1 je vetsi");
            return 0;
        }
    }
}
int vlozeniCisel(int pole[]) {
    int pocet=0, i=0;
    while (1) {
        int status;
        while ((status = scanf("%d", &pole[i])) != 1){
          pocet=cleanBuffer();
          if (pocet==1) return i;
          printf("Promin ale error");
        }
      i++;

    }
}

void tiskniPole(int pole[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ",pole[i]);
    }
    printf("\n");
}

int main() {
//    int pole1[] = {1,2,10,7,8};
//    int pole2[] = {1,2,9,8,6};
    int * pole1 = malloc(4000000);
    int * pole2 = malloc(4000000);
    printf("Prosim zadej radu cisel, ukoncenych libovolnym 1 znakem+ENTER: ");
    int n1=vlozeniCisel(pole1);
    printf("Prosim zadej radu cisel, ukoncenych libovolnym 1 znakem+ENTER: ");
    int n2=vlozeniCisel(pole2);
    tiskniPole(pole1,n1);
    tiskniPole(pole2,n2);
    return porovnejPoleCisel(pole1, pole2, n1<n2? n1:n2);

}
