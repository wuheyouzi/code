#include <stdio.h>
#include <stdlib.h>

int main() {
    char * c = calloc(1, sizeof(char));
    if (c == NULL) return -1;
    scanf("%c", c);
    int len = 1, cnt = 0;
    while (*(c + len - 1) != '\0'/* && *(c + len - 1) != '\n'*/) {
        if (*(c + len - 1) == 'm') {
            cnt++;
        }
        c = realloc(c, sizeof(char) * (len + 1));
        if (c == NULL) return -1;
        scanf("%c", c + len);
        if (*(c + len) == '\0' /* && *(c + len) == '\n'*/) {
            break;
        }
        len++;
    }

    len--;

    if (cnt) {
        printf("%d\n", cnt);
        return 0;
    }

    c = realloc(c, sizeof(char) * (len + 1));
    len++;
    if (c == NULL) return -1;
    for (int i = len; i > 2; i--) {
        *(c + i) = *(c + i - 1);
    }
    c[1] = 'm';
    printf("%s", c);

    free(c);
    return 0;
}