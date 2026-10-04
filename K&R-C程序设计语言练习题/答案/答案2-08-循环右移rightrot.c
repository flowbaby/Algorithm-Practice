/*
 * 答案2-08 循环右移rightrot
 *
 * 提示：每循环一次把 x 右移 1 位，被移出的最右位若为 1，则通过或运算
 * 补到最高位，循环 n 次即完成 n 位循环右移。先求出机器的字长 wordlength。
 * 注意 K&R 约定最右位为第 0 位。
 */
#include <stdio.h>

int wordlength(void)
{
    int i;
    unsigned v = ~0U;
    for (i = 1; (v = v >> 1) > 0; ++i)
        ;
    return i;
}

unsigned rightrot(unsigned x, int n)
{
    int rbit, w = wordlength();

    while (n-- > 0) {
        rbit = x & 1;
        x = x >> 1;
        if (rbit)
            x |= 1 << (w - 1);
    }
    return x;
}

void printbits(unsigned v)
{
    int i, w = wordlength();
    for (i = w - 1; i >= 0; --i)
        putchar((v >> i) & 1 ? '1' : '0');
    putchar('\n');
}

int main(void)
{
    unsigned x = 0x80000001;
    printf("x       = ");
    printbits(x);
    printf("rot1    = ");
    printbits(rightrot(x, 1));
    printf("rot4    = ");
    printbits(rightrot(x, 4));
    return 0;
}
