/*
 * 答案4-07 回退整个字符串ungets
 *
 * 提示：ungets 应当只使用 getch/ungetch 接口，而不应了解 buf/bufp 的内部细节，
 * 这样才能保持模块化、便于将来改动缓冲区实现。由于 ungetch 是“后进先出”，
 * 要使 getch 按原顺序读回字符串，必须把 s 从最后一个字符开始逆序推回。
 */
#include <stdio.h>
#include <string.h>

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

void ungets(char s[])
{
    int i, len;

    len = strlen(s);
    for (i = len - 1; i >= 0; i--)    /* 逆序推回，保证按原顺序读回 */
        ungetch(s[i]);
}

int main(void)
{
    char s[] = "hello";
    int i, c;

    ungets(s);
    printf("读取推回的字符串：");
    for (i = 0; i < (int) strlen(s); i++) {
        c = getch();
        putchar(c);
    }
    printf("\n");
    printf("再次调用 getch（缓冲区应已空，从标准输入读取）：");
    fflush(stdout);
    c = getch();
    printf("得到 '%c'\n", c);

    return 0;
}
