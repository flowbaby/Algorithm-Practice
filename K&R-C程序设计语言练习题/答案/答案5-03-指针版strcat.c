/*
 * 答案5-03 指针版strcat
 *
 * 提示：用指针遍历 s 到末尾，再把 t 中的字符逐一复制过去。
 * 指针版的关键写法是 while (*s) s++; 定位末尾，
 * 以及 while ((*s++ = *t++)) ; 把复制与判空合并。
 * 注意最后一个 '\0' 也会被复制，从而得到完整字符串。
 */
#include <stdio.h>

/* strcat: 把 t 连接到 s 的末尾（指针版） */
void strcat(char *s, char *t)
{
    while (*s)          /* 移到 s 末尾 */
        s++;
    while ((*s++ = *t++))   /* 复制 t（含结尾 '\0'） */
        ;
}

int main(void)
{
    char s[100] = "Hello, ";
    char t[] = "world!";

    strcat(s, t);
    printf("%s\n", s);
    return 0;
}
