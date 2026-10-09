/*
 * 答案3-04 itoa处理最大负数
 *
 * 提示：原版 itoa 对负数执行 n = -n 取绝对值，而最大负数 -(2^(字长-1)) 取负后
 * 仍溢出为自身，造成死循环或错误输出。修正办法：先把 n 转换成无符号整数再取绝对值，
 * 无符号运算不会溢出，可逐位取出数字；符号单独记录。
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>

void reverse(char s[]);

void itoa(int n, char s[])
{
    int i, sign;
    unsigned un;

    if ((sign = n) < 0)               /* 记录符号 */
        un = (unsigned) -n;           /* 无符号取绝对值，可安全处理 INT_MIN */
    else
        un = n;

    i = 0;
    do {                              /* 逆序生成数字 */
        s[i++] = un % 10 + '0';
    } while ((un /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';
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
    char s[40];

    itoa(INT_MIN, s);
    printf("INT_MIN = %d -> %s\n", INT_MIN, s);

    itoa(-12345, s);
    printf("-12345 -> %s\n", s);

    itoa(0, s);
    printf("0 -> %s\n", s);

    itoa(987654321, s);
    printf("987654321 -> %s\n", s);

    return 0;
}
