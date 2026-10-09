/*
 * 答案4-09 正确回退EOF
 *
 * 提示：EOF 被推回后，getch 应原样返回 EOF，其语义与 getchar 读到文件末尾一致，
 * 调用者据此结束输入。为此缓冲区必须是 int 类型（char 无法可靠存放 -1），
 * 并且 ungetch 用“缓冲是否已满”而不是字符值来判断，避免与 EOF 混淆。
 */
#include <stdio.h>

#define BUFSIZE 100

int buf[BUFSIZE];         /* int 缓冲区，可安全存放 EOF */
int bufp = 0;              /* buf 中下一个空闲位置 */

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

int main(void)
{
    int c;

    ungetch(EOF);                      /* 推回 EOF */
    c = getch();
    if (c == EOF)
        printf("推回的 EOF 被正确读回（getch 返回 EOF）\n");
    else
        printf("错误：getch 返回了 %d\n", c);

    return 0;
}
