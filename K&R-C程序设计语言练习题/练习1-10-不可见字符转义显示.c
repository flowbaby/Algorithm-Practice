/*
 * 练习1-10 不可见字符转义显示
 *
 * 题目：编写一个程序，将输入复制到输出，并用 \\t 代替制表符，用 \\b 代替退格符，用 \\\\ 代替反斜杠本身。这样可以将制表符和退格符以明确的方式显示出来。
 */
#include <stdio.h>

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            putchar('\\');
            putchar('t');
        } else if (c == '\b') {
            putchar('\\');
            putchar('b');
        } else if (c == '\\') {
            putchar('\\');
            putchar('\\');
        } else {
            putchar(c);
        }
    }

    return 0;
}