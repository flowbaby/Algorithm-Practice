/*
 * 答案3-06 带最小字段宽度的itoa
 *
 * 提示：在 3-04 无符号处理的基础上，数字（含符号）生成完毕后，若长度不足最小字段
 * 宽度 w，就在前面补空格。实现上先逆序生成数字、再补空格，最后整体反转；
 * 这样空格会落在字符串开头，恰好是左侧填充。
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);

void itoa(int n, char s[], int w)
{
    int i, sign;
    unsigned un;

    if ((sign = n) < 0)
        un = (unsigned) -n;
    else
        un = n;

    i = 0;
    do {                              /* 逆序生成数字 */
        s[i++] = un % 10 + '0';
    } while ((un /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';
    while (i < w)                     /* 用空格补齐到字段宽度 */
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int main(void)
{
    char s[50];

    itoa(-345, s, 10);
    printf("'%s'\n", s);

    itoa(INT_MIN, s, 15);
    printf("'%s'\n", s);

    itoa(42, s, 3);
    printf("'%s'\n", s);

    itoa(0, s, 1);
    printf("'%s'\n", s);

    return 0;
}
