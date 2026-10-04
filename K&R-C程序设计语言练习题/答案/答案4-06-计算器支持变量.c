/*
 * 答案4-06 计算器支持变量
 *
 * 提示：26 个小写字母作为变量名，值存于 variable[26]。getop 读到单个小写字母时
 * 预读下一个非空白字符：若是 '='，说明它是赋值目标，返回标记 'V'（主循环不压栈），
 * 否则按变量引用处理，压入变量当前值。'=' 把栈顶弹出存入变量；'p' 打印栈顶并
 * 存入最近值 last；'$' 把 last 压回栈。多字母单词仍按函数名（sin/exp/pow）处理。
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define NAME 'n'
#define VAR 'V'
#define MAXVAL 100
#define BUFSIZE 100

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;
int var;                       /* getop 最近见到的变量名 */
double variable[26];           /* 单字母变量的值 */
double last;                   /* 最近打印的值 */

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

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

int getop(char s[])
{
    int i, c, d;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (islower(c)) {                 /* 单字母变量 */
        var = c;
        d = getch();                  /* 预读：是否赋值？ */
        while (d == ' ' || d == '\t')
            d = getch();
        if (d == '=') {
            ungetch(d);               /* '=' 留给下一次 getop */
            return VAR;               /* 赋值目标：主循环不压栈 */
        }
        ungetch(d);
        return c;                     /* 变量引用 */
    }
    if (isalpha(c)) {                 /* 函数名 */
        i = 0;
        while (isalpha(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch(c);
        return NAME;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;                     /* 不是数字 */
    i = 0;
    if (c == '-') {                   /* 可能是负数 */
        c = getch();
        if (isdigit(c) || c == '.') {
            s[++i] = c;
        } else {
            ungetch(c);
            return '-';               /* 是减号运算符 */
        }
    }
    if (isdigit(c))                   /* 收集整数部分 */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')                     /* 收集小数部分 */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

int main(void)
{
    int type, i;
    double op2;
    char s[MAXOP];

    for (i = 0; i < 26; i++)
        variable[i] = 0.0;
    last = 0.0;

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case NAME:
            if (strcmp(s, "sin") == 0)
                push(sin(pop()));
            else if (strcmp(s, "exp") == 0)
                push(exp(pop()));
            else if (strcmp(s, "pow") == 0) {
                op2 = pop();
                push(pow(pop(), op2));
            } else
                printf("error: %s not supported\n", s);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case VAR:                     /* 赋值目标变量：不压栈 */
            break;
        case '=':                     /* 赋值：把栈顶存入变量 */
            if (islower(var))
                variable[var - 'a'] = pop();
            else
                printf("error: invalid variable name\n");
            break;
        case 'p':                     /* 打印栈顶，并存入 last */
            printf("\t%.8g\n", last = val[sp - 1]);
            break;
        case '$':                     /* 压入最近打印的值 */
            push(last);
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            if (islower(type))        /* 变量引用：压入变量值 */
                push(variable[type - 'a']);
            else
                printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}
