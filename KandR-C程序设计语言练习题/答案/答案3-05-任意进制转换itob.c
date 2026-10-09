/*
 * 答案3-05 任意进制转换itob
 *
 * 提示：itob 用“除基取余”法逐位得到 n 在 b 进制下的数字，余数 0~9 映射为
 * '0'~'9'，10~35 映射为 'A'~'Z'。数字按逆序产生，最后用 reverse 反转。
 * 用无符号数处理 n，可避免对最大负数取负时的溢出问题。
 */
#include <stdio.h>
#include <string.h>

void reverse(char s[]);

void itob(int n, char s[], int b)
{
    int i, sign;
    unsigned un, j;
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if ((sign = n) < 0)
        un = (unsigned) -n;
    else
        un = n;

    i = 0;
    do {
        j = un % b;
        s[i++] = digits[j];
    } while ((un /= b) > 0);

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
    char s[100];
    int n = 255;

    itob(n, s, 2);
    printf("%d base  2 = %s\n", n, s);
    itob(n, s, 8);
    printf("%d base  8 = %s\n", n, s);
    itob(n, s, 16);
    printf("%d base 16 = %s\n", n, s);
    itob(-255, s, 16);
    printf("%d base 16 = %s\n", -255, s);
    itob(123456789, s, 16);
    printf("123456789 base 16 = %s\n", s);

    return 0;
}
