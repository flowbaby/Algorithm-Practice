/*
 * 答案4-11 getop使用静态变量
 *
 * 提示：getop 不再调用 getch/ungetch，而是在函数内部用一个 static int 变量
 * 保存“多读出来的那个字符”：收集数字结束时，把末尾的非数字字符存进去，
 * 下次调用先取它再读新输入。这样词法分析的状态被封装在 getop 内部。
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

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

int getop(char s[])
{
    static int lastc = 0;             /* 内部回退字符，0 表示无 */
    int i, c;

    c = (lastc != 0) ? lastc : getchar();
    lastc = 0;

    while (c == ' ' || c == '\t')
        c = getchar();

    s[0] = c;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;                     /* 不是数字 */

    i = 0;
    if (isdigit(c))                   /* 收集整数部分 */
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.')                     /* 收集小数部分 */
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        lastc = c;                    /* 把多读的字符暂存起来 */
    return NUMBER;
}

int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
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
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}
