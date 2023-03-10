#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    int ch, ch2 = 0;

    // 0 for normal
    // 1 for //
    // 2 for // /*
    // 3 for /*
    // 4 for "
    // 5 for /* //
    int status = 0;

    while (1) {
        if (ch2 != 0) {
            ch = ch2;
            ch2 = 0;
        } else {
            ch = getchar();
        }
        
        if (ch == EOF) {
            break;
        }

        // read next char in some pattern
        if (ch == '/' || ch == '\\' || ch == '*') {
            ch2 = getchar();
        } else {
            ch2 = 0;
        }

        int should_comsume_two = 0;

        if (ch == '/' && ch2 == '/') {
            should_comsume_two = 1;
        }
        if (ch == '/' && ch2 == '*') {
            should_comsume_two = 1;
        }
        if (ch == '*' && ch2 == '/') {
            should_comsume_two = 1;
        }
        if (ch == '\\' && ch2 == '\"') {
            should_comsume_two = 1;
        }
        if (ch == '\\' && ch2 == '\n') {
            should_comsume_two = 1;
        }
        
        if (!should_comsume_two) {  // only 1 ch should be considered 
            if (status == 0) {
                if (ch == '\"') {
                    status = 4;
                }
            } else if (status == 1) {
                if (ch == '\n') {
                    status = 0;
                    printf(" */");
                }
            } else if (status == 2) {
                if (ch == '\n') {
                    status = 0;
                    printf(" */");
                }
            } else if (status == 4) {
                if (ch == '\"') {
                    status = 0;
                }
            } else if (status == 5) {
                if (ch == '\n') {
                    status = 3;
                    printf(" */");
                }
            }
            putchar(ch);
        } else {  // should consider (ch, ch2) continuous char
            if (status == 0) {
                if (ch == '/' && ch2 == '/') {
                    status = 1;
                    printf("/*");
                } else if (ch == '/' && ch2 == '*') {
                    status = 3;
                    printf("/*");
                } else {
                    putchar(ch);
                    putchar(ch2);
                }
            } else if (status == 1) {
                if (ch == '/' && ch2 == '*') {
                    status = 2;
                } else if (ch == '\\' && ch2 == '\n') {
                    putchar('\n');
                } else {
                    putchar(ch);
                    putchar(ch2);
                }
            } else if (status == 2) {
                if (ch == '*' && ch2 == '/') {
                    status = 1;
                } else {
                    putchar(ch);
                    putchar(ch2);
                }
            } else if (status == 3) {
                if (ch == '*' && ch2 == '/') {
                    status = 0;
                    printf("*/");
                } else if (ch == '/' && ch2 == '/') {
                    status = 5;
                    printf("/*");
                } else {
                    putchar(ch);
                    putchar(ch2);
                }
            } else if (status == 4) {
                putchar(ch);
                putchar(ch2);
            } else if (status == 5) {
                if (ch == '*' && ch2 == '/') {
                    status = 0;
                    printf("*/");
                } else if (ch == '\\' && ch2 == '\n') {
                    putchar('\n');
                } else {
                    putchar(ch);
                    putchar(ch2);
                }
            }

            ch2 = 0;  // comsume the next char
        }
    }

    if (status == 1) {
        printf(" */");
    } else if (status == 2) {
        printf(" */");
    }
    
    return 0;
}
