/*
 * 答案5-06 指针改写早期程序
 *
 * 提示：把第 1~4 章的常用例程统一改成指针实现——getline 用两个指针
 * 相减求行长度，atoi 用 while(isdigit(*s)) 边移动指针边累加，
 * itoa 用指针把数字写入字符串后再调用 reverse 倒置，reverse 用首尾
 * 两个指针交换字符，strindex 用三重指针做模式匹配。
 * 指针版的核心是把“下标 + 数组名”替换为“移动指针 + 解引用”。
 */
#include <ctype.h>
#include <stdio.h>

#define MAXLINE 1000

/* getline: 读入一行到 s，返回其长度（指针版） */
int getline(char *s, int lim)
{
    int c;
    char *t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - t;
}

/* atoi: 把字符串 s 转换为整数（指针版） */
int atoi(char *s)
{
    int n = 0, sign;

    while (isspace(*s))
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    while (isdigit(*s))
        n = 10 * n + (*s++ - '0');
    return sign * n;
}

/* reverse: 倒置字符串 s（指针版） */
void reverse(char *s)
{
    char *t = s, c;

    while (*t)          /* 走到末尾 */
        t++;
    t--;                /* 回退到最后一个字符 */
    for ( ; s < t; s++, t--) {
        c = *s;
        *s = *t;
        *t = c;
    }
}

/* itoa: 把整数 n 转换为字符串 s（指针版） */
void itoa(int n, char *s)
{
    int sign;
    char *t = s;

    if ((sign = n) < 0)     /* 记录符号 */
        n = -n;
    do {                    /* 逆序生成数字字符 */
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(t);
}

/* strindex: 返回 t 在 s 中的位置，若不存在返回 -1（指针版） */
int strindex(char *s, char *t)
{
    char *p, *q, *r;

    for (p = s; *p; p++) {
        for (q = p, r = t; *r && *q == *r; q++, r++)
            ;
        if (*r == '\0')
            return p - s;
    }
    return -1;
}

int main(void)
{
    char line[MAXLINE];
    char buf[20];
    int n;

    printf("输入一行文本：");
    if (getline(line, MAXLINE) > 0) {
        printf("读到的行：%s", line);
        printf("atoi(\"  -123\") = %d\n", atoi("  -123"));
        itoa(-12345, buf);
        printf("itoa(-12345) = \"%s\"\n", buf);
        printf("strindex(\"%s\", \"ell\") = %d\n", line, strindex(line, "ell"));
    }
    return 0;
}
