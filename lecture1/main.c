#include <stdio.h>
#include <stdbool.h>

int main() {
    int ch;
    int n = 0;
    int line = 0;
    int word = 0;

    bool in_a_word = false;

    printf("Enter text: \n");

    while ((ch = getchar()) != EOF) {
        // chars
        ++n;

        // lines
        if (ch == '\n') {
            ++line;
        }

        // word
        bool in_A_to_Z = 'A' <= ch && ch <= 'Z';
        bool in_a_to_z = 'a' <= ch && ch <= 'z';
        bool in_0_to_9 = '0' <= ch && ch <= '9';
        bool is_word_ch = in_A_to_Z || in_a_to_z || in_0_to_9;
        if (is_word_ch) {
            if (!in_a_word) {
                in_a_word = true;
                ++word;
            }
        } else {
            in_a_word = false;
        }
    }

    printf("Lines:    %3d\n", line);
    printf("Words:    %3d\n", word);
    printf("Chars:    %3d\n", n);

    return 0;
}
