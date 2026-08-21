#include <stdio.h>

int main()
{
    int c;
    const int IN = 1;
    const int OUT = 0;
    int state = OUT;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                putchar('\n');
                state = OUT;
            }
        } else {
            putchar(c);
            state = IN;
        }
    }

    return 0;
}