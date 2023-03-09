#include <stdio.h>

int main() {
    char ch;
    int n = 0;
    int line = 0;

    printf("Enter text: \n");

    while ((ch = getchar()) != EOF) {
        ++n;
        if (ch == '\n') {
            ++line;
        }
    }

    printf("Lines:    %3d\n", line);
    printf("Chars:    %3d\n", n);

    return 0;
}
