/*
 * 答案2-09 快速位计数bitcount
 *
 * 提示：设 x 的二进制表示中，最右边的 1 位于第 k 位（最右位为第 0 位），
 * 即第 k 位为 1、其右侧全为 0。计算 x-1 时需向第 k 位借位：第 k 位由 1
 * 变 0，其右侧所有 0 变为 1，第 k 位以左各位保持不变。因此
 * x & (x-1) 中：第 k 位为 1 & 0 = 0，其右侧为 0 & 1 = 0，更高位保持原值
 * ——恰好删除了最右边的 1 位。例如 x = 10110000 时，x-1 = 10101111，
 * x & (x-1) = 10100000。原版 bitcount 逐位测试每一位；改进版每执行一次
 * x &= (x-1) 就删除一个 1，循环次数等于 1 的个数，平均更快。演示代码如下。
 */
#include <stdio.h>

/* 原版：逐位测试 */
int bitcount_old(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 1)
            ++b;
    return b;
}

/* 改进版：每次循环删除最右边的 1 */
int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x &= (x - 1))
        ++b;
    return b;
}

int main(void)
{
    printf("0x0F: old=%d new=%d\n", bitcount_old(0x0F), bitcount(0x0F));
    printf("0xFF: old=%d new=%d\n", bitcount_old(0xFF), bitcount(0xFF));
    printf("0x80000000: old=%d new=%d\n",
           bitcount_old(0x80000000), bitcount(0x80000000));
    return 0;
}
