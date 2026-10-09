/*
 * 答案5-10 命令行逆波兰求值expr
 *
 * 提示：遍历 argv 的每个参数，若是数字（含负数与小数的判断）就
 * 压栈，若是运算符就从栈中弹出操作数计算后压回；'-' 与 '/' 要
 * 注意操作数顺序（后弹出的在左边）。程序结束时弹出栈顶作为结果。
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

double stack[MAXOP];    /* 操作数栈 */
int sp = 0;             /* 下一个空闲栈位置 */

void push(double f)
{
    if (sp < MAXOP)
        stack[sp++] = f;
    else
        printf("错误：栈满\n");
}

double pop(void)
{
    if (sp > 0)
        return stack[--sp];
    else {
        printf("错误：栈空\n");
        return 0.0;
    }
}

/* 判断参数是否表示一个数（支持正负号、小数点和数字） */
int isnum(char *s)
{
    if (isdigit(s[0]) || s[0] == '.')
        return 1;
    if ((s[0] == '+' || s[0] == '-') && (isdigit(s[1]) || s[1] == '.'))
        return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    double op2;

    while (--argc > 0) {
        char *arg = *++argv;
        if (isnum(arg))
            push(atof(arg));
        else
            switch (arg[0]) {
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
                    printf("错误：除数为零\n");
                break;
            default:
                printf("错误：未知命令 %s\n", arg);
                break;
            }
    }
    printf("%.8g\n", pop());
    return 0;
}
