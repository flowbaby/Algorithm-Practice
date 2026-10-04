/*
 * 答案4-08 单字符回退
 *
 * 提示：既然最多只会有一个字符被推回，缓冲区可以退化为单个 int 变量。
 * ungetch 在已有回退字符时报错（或忽略），getch 有回退字符时先返回它，
 * 否则读标准输入。bufp 只需表示“是否有回退字符”两个状态。
 */
#include <stdio.h>

int buf;                  /* 单个字符的回退缓冲区 */
int bufp = 0;             /* 0 表示空，非 0 表示已有一个回退字符 */

int getch(void)
{
    if (bufp > 0) {
        bufp = 0;
        return buf;
    } else
        return getchar();
}

void ungetch(int c)
{
    if (bufp > 0)
        printf("ungetch: too many characters\n");
    else {
        buf = c;
        bufp = 1;
    }
}

int main(void)
{
    int c;

    ungetch('x');
    c = getch();
    printf("第一个 getch 返回：%c\n", c);
    c = getch();
    printf("第二个 getch 返回：%c\n", c);

    return 0;
}
