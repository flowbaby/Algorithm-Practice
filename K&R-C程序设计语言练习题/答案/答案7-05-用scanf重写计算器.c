/*
 * 答案7-05 用scanf重写计算器
 *
 * 提示：第4章计算器用 getop 逐字符识别记号，这里改为直接 scanf("%s") 每次读入一个以空白分隔的记号：isdigit 判断是数字就用 atof 转换并压栈，否则按单字符操作符处理。%s 天然跳过空白，因此 \n 也被当作一个记号的第一个字符，需要显式处理（这里作为空命令忽略）。栈操作 push/pop 沿用第4章实现。
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

double stack[MAXOP];   /* 值栈 */
int sp = 0;            /* 下一个空闲栈位置 */

void push(double f)
{
    if (sp < MAXOP)
        stack[sp++] = f;
    else
        printf("error: stack full\n");
}

double pop(void)
{
    if (sp > 0)
        return stack[--sp];
    printf("error: stack empty\n");
    return 0.0;
}

/* 后缀表达式计算器：scanf 读记号，atof 做数字转换 */
int main(void)
{
    char s[MAXOP];
    double op2;

    while (scanf("%s", s) != EOF) {
        if (isdigit(s[0]) || (s[0] == '-' && isdigit(s[1])) || s[0] == '.') {
            push(atof(s));
            continue;
        }
        switch (s[0]) {
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
