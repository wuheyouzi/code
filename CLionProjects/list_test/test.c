#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char c[10000];
    scanf("%s", c);

    int cnt = 0;
    for (int i = 0; i <= strlen(c) - 1; i++) {
        if (c[i] == 'm') {
            cnt++;
        }
    }
    if (cnt) {
        printf("%d\n", cnt);
        exit(0);
    }
    for (int i = strlen(c) - 1; i >= 1; i--) {
        c[i + 1] = c[i];
    }
    c[1] = 'm';

    printf("%s", c);
    return 0;
}
