/*
 * 答案5-04 判断字符串结尾strend
 *
 * 提示：先分别用指针走到 s 和 t 的末尾，再从后往前逐一比较字符。
 * 当 t 被完整比完（t 指针回退到起点之前）且途中字符全部相等时，
 * t 就出现在 s 的末尾，返回 1，否则返回 0。
 */
#include <stdio.h>

/* strend: 若 t 出现在 s 的末尾返回 1，否则返回 0 */
int strend(char *s, char *t)
{
    char *bs = s;       /* 保存 s 的起点 */
    char *bt = t;       /* 保存 t 的起点 */

    while (*s)          /* 走到 s 末尾 */
        s++;
    while (*t)          /* 走到 t 末尾 */
        t++;
    for ( ; s >= bs && t >= bt && *s == *t; s--, t--)
        ;
    if (t < bt)         /* t 全部匹配完 */
        return 1;
    return 0;
}

int main(void)
{
    char s1[] = "hello world";
    char t1[] = "world";
    char t2[] = "hello";
    char t3[] = "orld";

    printf("strend(\"%s\", \"%s\") = %d\n", s1, t1, strend(s1, t1));
    printf("strend(\"%s\", \"%s\") = %d\n", s1, t2, strend(s1, t2));
    printf("strend(\"%s\", \"%s\") = %d\n", s1, t3, strend(s1, t3));
    return 0;
}
