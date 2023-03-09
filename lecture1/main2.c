#include <stdio.h>
#include <stdbool.h>

int main() {
    int ch;
    int n = 0;
    int line = 0;
    int space = 0;

    bool in_space_gap_flag = false;

    printf("Enter text: \n");

    /**
     * We need to make sure the input follow the below rules,
     * or it will give wrong answer:
     * 1) There is no extra space at the end of each line;
     * 2) There must be a space after each punctuation that not at the end of the line;
     * 3) There is no empty line except the last line;
     */

    while ((ch = getchar()) != EOF) {
        // chars
        ++n;

        if (ch == ' ') {
            if (!in_space_gap_flag) {
                ++space;
                in_space_gap_flag = true;
            }
        } else if (ch == '\n') {
            ++line;
        } else {
            in_space_gap_flag = false;
        }
    }

    printf("Lines:    %3d\n", line);
    printf("Words:    %3d\n", space + line);
    printf("Chars:    %3d\n", n);

    return 0;
}
