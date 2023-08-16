#include <stdio.h>
#include <stdbool.h>
int main() {
    int poleA[]={1, 2,3};
    int poleB[]={1, 2,3};
    char retA[]={'A', 'h', 'o', 'j', 0};
    char retB[]={'A', 'h', 'o', 'j', 0};

    printf("Adresa poleA=%llu\n", poleA);
    printf("Adresa poleB=%llu\n", poleB);

    puts(retB);
    if (poleA==poleB) printf("jsou rovna\n");
    else if (poleA<poleB) printf("poleA je mensi\n");
        printf("Adresa poleA je vetsi\n");

    if (retA==retB) printf("Retezce jsou rovne\n");
    else if (poleA<poleB) printf("retA je mensi\n");
    printf("Adresa retA je vetsi\n");
    bool stejne=true;
    for (int i=0; i<sizeof (retA); i++ ) {
        if (retA[i]>retB[i]) {
            printf("retA je vetsi\n");
            stejne=false;
            break;
        }
        else if (retA[i]<retB[i]) {
            printf("retA je mensi\n");
            stejne=false;
            break;
        }
    }
    if (stejne) printf("retA==retB\n");
}
