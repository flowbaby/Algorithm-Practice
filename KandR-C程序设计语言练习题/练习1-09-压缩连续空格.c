/*
 * 练习1-09 压缩连续空格
 *
 * 题目：编写一个程序，将输入复制到输出，并把其中连续的一个或多个空格用一个空格代替。
 */
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