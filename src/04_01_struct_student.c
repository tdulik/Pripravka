#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char jmeno[80];
    int znamky[10];
    double minuly_prumer;
} tStudent;

void usekniOdradkovani(char ret[]) {
    for (int i=0; ret[i] != 0; i++) {
        if (ret[i]=='\n') {
            ret[i]=0;
            break;
        }
    }
}
void tiskni(tStudent student) {
    usekniOdradkovani(student.jmeno);
    printf("Jmeno: %s, ", student.jmeno);
    for (int i=0; i<sizeof(student.znamky)/sizeof(int); i++) {
        if (student.znamky[i]>0)
            printf("znamka[%d]=%d, ", i, student.znamky[i]);
    }
    printf("minuly prumer=%lf\n", student.minuly_prumer);
}

int main() {
    tStudent franta={"Franta Dobrota", {1,2,1,1,}};
    tiskni(franta);
    tStudent anna={"Anna"};
    tiskni(anna);
    tStudent st={"", {0}, 0};
    puts("Zadejte jmeno:");
    //scanf("%s", st.jmeno); // nacte pouze 1 slovo
    fgets(st.jmeno, sizeof (st.jmeno), stdin); // nacte cely radek
    puts("Zadejte minuly prumer:");
    scanf("%lf", &st.minuly_prumer);
    puts("Zadejte znamky jako cela cisla, oddelena mezerou:");
    for (int i=0; i<sizeof(st.znamky)/sizeof(int); i++) {
        int status = scanf("%d", &st.znamky[i]);
        if (status<1) {
            puts("Konec zadavani (zadali jste ne-int)");
            break;
        }
    }
    tiskni(st);
    return 0;
}

