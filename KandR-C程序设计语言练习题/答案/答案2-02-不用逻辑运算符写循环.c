/*
 * 答案2-02 不用逻辑运算符写循环
 *
 * 提示：for 循环的三个条件（i < lim-1、(c=getchar()) != '\n'、c != EOF）
 * 可改写为逐个判断的 if-else 结构。用枚举变量 okloop 作为循环开关，
 * 任一条件不满足即置 NO 退出循环，从而不用 && 或 ||。
 */
#include <stdio.h>
#define MAXLINE 1000

enum loop { NO, YES };
enum loop okloop = YES;

int main(void)
{
    char s[MAXLINE];
    int i, c, lim = MAXLINE;

    i = 0;
    while (okloop == YES) {
        if (i >= lim - 1)
            okloop = NO;
        else if ((c = getchar()) == '\n')
            okloop = NO;
        else if (c == EOF)
            okloop = NO;
        else {
            s[i] = c;
            ++i;
        }
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    printf("read: %s\n", s);
    return 0;
}
