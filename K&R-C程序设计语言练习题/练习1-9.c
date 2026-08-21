#include <stdio.h>

int main()
{
    int c;
    int count = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (count >= 1)
                ;
            else
                putchar(c);
            count++;
        } else {
            count = 0;
            putchar(c);
        }
    }

    return 0;
}