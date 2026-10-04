/*
 * 练习1-06 验证getchar不等于EOF
 *
 * 题目：验证表达式 getchar() != EOF 的值是 0 还是 1。
 */
#include <stdio.h>

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        putchar(c);
    }

    return 0;
}