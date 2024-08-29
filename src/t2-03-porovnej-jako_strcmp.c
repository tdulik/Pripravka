#include <stdio.h>
#include "string.h"

// nase vlastni implementace fce strcmp z string.h
int porovnej(char * str1, char * str2) {
    while (*str1!=0 && *str2!=0 && (*str1 == *str2)) {
        str1++; str2++;
    };
    int vysledek=*str1-*str2;
    if (vysledek <0) return -1;
    else return (vysledek>0);
}

int main(int argc, char *argv[]) {
    printf("strcmp =%d\n", strcmp("AA", "AAA"));
    printf("porovnej =%d\n", porovnej("AA", "AAA"));
}
