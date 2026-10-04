/*
 * 答案1-23 删除C程序注释
 *
 * 提示：分三种状态处理：普通字符（遇到 / 时读下一个字符判断是否 /* 注释开头）、注释内（一直读到 */ 为止，C 注释不嵌套）、引号内（字符串与字符常量原样输出，遇到反斜杠时跳过其后的转义字符）。注意对 / 不是注释开头的情况要把两个字符都原样输出。
 */
#include <stdio.h>

void rcomment(int c);
void in_comment(void);
void echo_quote(int c);

/* remove all comments from a valid C program */
int main()
{
    int c;

    while ((c = getchar()) != EOF)
        rcomment(c);
    return 0;
}

/* rcomment: read each character, print it if not inside a comment */
void rcomment(int c)
{
    int d;

    if (c == '/') {
        if ((d = getchar()) == '*')
            in_comment();           /* beginning comment */
        else if (d == '/') {
            putchar(c);             /* another slash */
            rcomment(d);
        } else {
            putchar(c);             /* not a comment */
            putchar(d);
        }
    } else if (c == '\'' || c == '"')
        echo_quote(c);              /* quote begins */
    else
        putchar(c);                 /* not a comment */
}

/* in_comment: inside a valid comment */
void in_comment(void)
{
    int c, d;

    c = getchar();                  /* prev character */
    d = getchar();                  /* curr character */
    while (c != '*' || d != '/') {  /* search for end */
        c = d;
        d = getchar();
    }
}

/* echo_quote: copy characters until quote ends */
void echo_quote(int c)
{
    int d;

    putchar(c);
    while ((d = getchar()) != c) {  /* search for end */
        if (d == '\\')
            putchar(getchar());     /* ignore escape sequence */
        else
            putchar(d);
    }
    putchar(d);
}
