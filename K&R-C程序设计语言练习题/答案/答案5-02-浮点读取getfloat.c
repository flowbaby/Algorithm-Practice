/*
 * 答案5-02 浮点读取getfloat
 *
 * 提示：getfloat 是 getint 的浮点版本，函数值仍返回 int——EOF 表示结束、
 * 0 表示读到的不是数、非零表示成功读到一个浮点数。实现时先按 getint 的
 * 方式读取符号与整数部分，再处理小数点后的小数部分，并用 power 累计小数
 * 位数以便最后除以相应的 10 的幂。符号也要像 getint 那样在符号后无数字
 * 时把字符压回输入。
 */
#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getfloat: 读取下一个浮点数并存入 *pn；返回 EOF、0 或非零 */
int getfloat(double *pn)
{
    int c, sign;
    double power;

    while (isspace(c = getch()))    /* 跳过空白 */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int d = getch();
        if (!isdigit(d) && d != '.') {
            ungetch(d);
            ungetch(c);
            return 0;
        }
        c = d;
    }
    for (*pn = 0.0; isdigit(c); c = getch())    /* 整数部分 */
        *pn = 10.0 * *pn + (c - '0');
    if (c == '.')                               /* 小数点 */
        c = getch();
    for (power = 1.0; isdigit(c); c = getch()) { /* 小数部分 */
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }
    *pn *= sign / power;
    if (c != EOF)
        ungetch(c);
    return (c != EOF) ? 1 : EOF;
}

int main(void)
{
    int n;
    double val;

    while ((n = getfloat(&val)) != EOF)
        if (n > 0)
            printf("读到浮点数: %g\n", val);
    return 0;
}
