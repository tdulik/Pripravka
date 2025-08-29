#include <stdio.h>
#include <stdint.h>
#include <locale.h>
#include <stdlib.h>


// ==========================
// Pole českých znaků (Unicode)
// ==========================
const unsigned char ceske_znaky[] =  "ÁČĎÉĚÍŇÓŘŠŤÚŮÝŽáčďéěíňóřšťúůýž";
char latin_znaky[] =                 "ACDEEINORSTUUYZacdeeinorstuuyz";
// ==========================
// Hlavní funkce
// ==========================
int main() {
    // Nastaví locale na české prostředí s UTF-8
    const unsigned char text[] = "ěšč Tohle je nějaký český text: Žluťoučký kůň úpěl ďábelské ódy.";

    printf("Prohledávám text:\n%s\n\n", text);

    char *vystup = malloc(1000);
    int k = 0;
    for (int i = 0; i < sizeof(text) / sizeof(text[0]); i++) {
        const char *found;
        int j;
        if(text[i] < 128) {
            vystup[k++] = text[i];
            continue;
        }
        for(j = 0; j < sizeof(ceske_znaky) / sizeof(ceske_znaky[0]); j+=2) {
            if (ceske_znaky[j] == text[i] && ceske_znaky[j + 1] == text[i + 1]) {
                vystup[k++] = latin_znaky[j/2];
                break;
            }
        }
    }

    return 0;
}
