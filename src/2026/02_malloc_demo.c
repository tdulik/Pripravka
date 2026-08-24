#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Malloc demo - stiskni klavesu ENTER!\n");
    char * uk = (char*)malloc(16000000000);
    if (uk == NULL) {
        printf("Malloc ERROR!\n");
        return -1;
    }
    for (long long int i = 0; i < 16000000000; i++) {
        uk[i] = i;
    }
    getchar();
    printf("Stiskni ENTER pro uvolneni pameti!\n");
    free(uk);
    getchar();
    printf("Stiskni ENTER pro konec!\n");
    return 0;
}
