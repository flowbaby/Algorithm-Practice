/*
 * 答案5-05 strncpy-strncat-strncmp
 *
 * 提示：三个函数都以 n 为上限，语义与标准库一致——strncpy 在 t 不足
 * n 个字符时用 '\0' 填充剩余位置；strncat 连接至多 n 个字符后必须补
 * 一个 '\0'；strncmp 至多比较 n 个字符，遇到 '\0' 即结束并返回差值。
 * 均用指针实现，并加后缀 2 以避免与标准库函数重名。
 */
#include <stdio.h>

/* strncpy2: 把至多 n 个字符从 t 复制到 s；t 不足时用 '\0' 填充 */
void strncpy2(char *s, char *t, int n)
{
    while (*t && n-- > 0)
        *s++ = *t++;
    while (n-- > 0)
        *s++ = '\0';
}

/* strncat2: 把 t 中至多 n 个字符连接到 s 末尾，并保证以 '\0' 结尾 */
void strncat2(char *s, char *t, int n)
{
    while (*s)
        s++;
    while (*t && n-- > 0)
        *s++ = *t++;
    *s = '\0';
}

/* strncmp2: 比较 s 与 t 的前至多 n 个字符，返回差值 */
int strncmp2(char *s, char *t, int n)
{
    for ( ; n > 0 && *s == *t; s++, t++, n--)
        if (*s == '\0')
            return 0;
    return (n > 0) ? *s - *t : 0;
}

int main(void)
{
    char s[20];
    char t[] = "hello";

    strncpy2(s, t, 10);
    printf("strncpy2: \"%s\"\n", s);

    s[0] = 'x';
    s[1] = '\0';
    strncat2(s, t, 3);
    printf("strncat2: \"%s\"\n", s);

    printf("strncmp2(\"%s\", \"%s\", 3) = %d\n", t, "hell", strncmp2(t, "hell", 3));
    printf("strncmp2(\"%s\", \"%s\", 4) = %d\n", t, "hell", strncmp2(t, "hell", 4));
    return 0;
}
