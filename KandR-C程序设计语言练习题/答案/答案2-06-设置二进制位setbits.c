/*
 * 答案2-06 设置二进制位setbits
 *
 * 提示：构造 n 位全 1 的掩码 ~(~0 << n)，再左移到起始位置 p+1-n。
 * x 与该掩码取反后相与可清空目标位段；y 与掩码相与取出右 n 位后
 * 左移到位，两者相或即得结果。注意 K&R 约定最右位为第 0 位。
 */
#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return (x & ~(~(~0 << n) << (p + 1 - n))) |
           ((y & ~(~0 << n)) << (p + 1 - n));
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
    unsigned x = 0xFFFF, y = 0x0F05;
    printf("x       = ");
    printbits(x);
    printf("y       = ");
    printbits(y);
    printf("result  = ");
    printbits(setbits(x, 8, 4, y));
    return 0;
}
