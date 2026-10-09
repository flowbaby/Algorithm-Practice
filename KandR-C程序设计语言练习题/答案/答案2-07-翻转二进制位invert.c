/*
 * 答案2-07 翻转二进制位invert
 *
 * 提示：n 位全 1 掩码 ~(~0 << n) 左移到 p+1-n 处，与 x 做异或运算
 * 即可翻转目标位段，其余位不变。注意 K&R 约定最右位为第 0 位。
 */
#include <stdio.h>

unsigned invert(unsigned x, int p, int n)
{
    return x ^ (~(~0 << n) << (p + 1 - n));
}

void printbits(unsigned v)
{
    int i;
    for (i = 31; i >= 0; --i)
        putchar((v >> i) & 1 ? '1' : '0');
    putchar('\n');
}

int main(void)
{
    unsigned x = 0xF0F0;
    printf("x       = ");
    printbits(x);
    printf("result  = ");
    printbits(invert(x, 8, 4));
    return 0;
}
