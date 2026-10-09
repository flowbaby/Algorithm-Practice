/*
 * 答案5-01 修复getint符号处理
 *
 * 提示：在读到 + 或 - 之后，必须再读一个字符来确认它是否后跟数字。
 * 若后跟的不是数字，则要把该字符与符号一起 ungetch 压回输入流并返回 0
 * （表示本次未读到整数）；若后跟数字，则从该数字继续累积整数部分。
 * 注意 ++/-- 等运算符也会先读到符号，因此符号后必须紧跟数字才算有效输入。
 */
#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];      /* 供 ungetch 使用的缓冲区 */
int bufp = 0;           /* buf 中下一个空闲位置 */

int getch(void)         /* 取一个字符（可能是压回的字符） */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)     /* 把字符压回输入 */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getint: 从输入中读取下一个整数并存入 *pn；返回 EOF 表示结束，
 * 0 表示下一个输入不是数字，否则返回非零值表示成功读取 */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))    /* 跳过空白 */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);                 /* 不是数字 */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {     /* 处理符号后必须跟数字的情况 */
        int d = getch();
        if (!isdigit(d)) {
            ungetch(d);             /* 把非数字字符压回 */
            ungetch(c);             /* 把符号也压回 */
            return 0;
        }
        c = d;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return (c != EOF) ? 1 : EOF;
}

int main(void)
{
    int n, val;

    while ((n = getint(&val)) != EOF)
        if (n > 0)
            printf("读到整数: %d\n", val);
    return 0;
}
