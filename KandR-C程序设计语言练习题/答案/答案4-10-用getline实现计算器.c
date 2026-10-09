/*
 * 答案4-10 用getline实现计算器
 *
 * 提示：用 getline 一次读入整行，getop 从行内用下标扫描取记号，不再需要
 * getch/ungetch。getop 中把当前行与行内位置做成 static 变量；当行被消费完
 * （line[li] == '\0'）时自动读下一行，getline 返回 0 或负数表示输入结束，
 * getop 返回 EOF。遇到 '\n' 时返回 '\n'，主循环照常打印栈顶。
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define MAXLINE 1000

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

int getline(char line[], int limit)
{
    int i, c;

    for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        line[i] = c;
    if (c == '\n') {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

int getop(char s[])
{
    static char line[MAXLINE];
    static int li = 0;
    int i, c;

    for (;;) {
        if (line[li] == '\0') {       /* 当前行已消费完：读新行 */
            if (getline(line, MAXLINE) <= 0)
                return EOF;
            li = 0;
        }
        while ((s[0] = c = line[li++]) == ' ' || c == '\t')
            ;
        if (c != '\0')
            break;                    /* 取到一个有效字符 */
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;                     /* 不是数字 */
    i = 0;
    if (isdigit(c))                   /* 收集整数部分 */
        while (isdigit(s[++i] = c = line[li++]))
            ;
    if (c == '.')                     /* 收集小数部分 */
        while (isdigit(s[++i] = c = line[li++]))
            ;
    s[i] = '\0';
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
