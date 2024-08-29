#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char jmeno[100];
    double vyska, vaha, vek;
} tData;

typedef struct _tNode {
    tData data;
    struct _tNode * next;
} tNode;

typedef struct {
    tNode * first;
    int size;
} tList;

void insertFirst(tList *l, tData d) {
    tNode *uk = malloc(sizeof (tNode));
    if (uk==NULL) {
        puts("error allocating memorry");
        exit(0);
    }
    uk->data=d;
    uk->next=l->first;
    l->first=uk;
}

void printList(tList list){
    tNode * uk=list.first;
    while(uk!=NULL){
        printf("Jmeno: %s, ",uk->data.jmeno);
        printf("Vaha: %lf, ",uk->data.vaha);
        printf("Vek: %lf, ",uk->data.vek);
        printf("Vyska: %lf\n",uk->data.vyska);
        uk=uk->next;
    }
}

int main(int argc, char *argv[]) {
    tList seznam={NULL, 0};
    insertFirst(&seznam, (tData){"Franta", 180, 80, 30});
    insertFirst(&seznam, (tData){"Daniel", 175, 70, 28});
    insertFirst(&seznam, (tData){"David", 190, 88, 36});
    printList(seznam);
}
