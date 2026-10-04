/*
 * 答案4-12 递归版itoa
 *
 * 提示：模仿 printd：先递归处理 n/10，回溯时再写出当前位的数字，天然得到
 * 正确顺序。static 下标 i 在最深层（n/10 == 0）时重置为 0 并写符号位，
 * 回溯时逐位填入；用 abs(n % 10) 取数字，可安全处理 INT_MIN 而不溢出。
 */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void itoa(int n, char s[])
{
    static int i;                     /* static：递归各层共享 */

    if (n / 10)
        itoa(n / 10, s);
    else {
        i = 0;                        /* 最深层：重置下标并写符号 */
        if (n < 0)
            s[i++] = '-';
    }
    s[i++] = abs(n % 10) + '0';
    s[i] = '\0';
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
