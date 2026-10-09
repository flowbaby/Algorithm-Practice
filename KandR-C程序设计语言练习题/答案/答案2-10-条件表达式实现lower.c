/*
 * 答案2-10 条件表达式实现lower
 *
 * 提示：原函数用 if-else 判断 c 是否为大写字母，是则加 'a'-'A' 转换为
 * 小写。用条件表达式可写成一行：
 * c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c。
 */
#include <stdio.h>

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main(void)
{
    char s[] = "Hello, World! 123";
    int i;
    for (i = 0; s[i] != '\0'; ++i)
        putchar(lower(s[i]));
    putchar('\n');
    return 0;
}
