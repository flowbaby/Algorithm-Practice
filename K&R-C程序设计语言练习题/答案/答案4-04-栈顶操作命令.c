/*
 * 答案4-04 栈顶操作命令
 *
 * 提示：新增四条单字符命令——'p' 打印栈顶但不弹出（直接读 val[sp-1]）、
 * 'd' 复制栈顶（把栈顶再压入一份）、's' 交换栈顶两个元素、'c' 清空栈（把 sp 置 0）。
 * 栈数组与栈顶指针在同一文件内可见，命令分支可直接访问。
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

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
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;                     /* 不是数字 */
    i = 0;
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
    int type;
    double op1, op2;
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
        case 'p':                     /* 打印栈顶，不弹出 */
            printf("\t%.8g\n", val[sp - 1]);
            break;
        case 'd':                     /* 复制栈顶 */
            push(val[sp - 1]);
            break;
        case 's':                     /* 交换栈顶两个元素 */
            op1 = pop();
            op2 = pop();
            push(op1);
            push(op2);
            break;
        case 'c':                     /* 清空栈 */
            sp = 0;
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
