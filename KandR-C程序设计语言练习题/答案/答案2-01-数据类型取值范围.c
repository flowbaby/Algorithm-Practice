/*
 * 答案2-01 数据类型取值范围
 *
 * 提示：方法一直接打印 <limits.h> 与 <float.h> 中定义的范围宏；
 * 方法二直接计算——无符号类型的最大值即全 1 位模式，可用 (T)-1 得到；
 * 有符号类型让值不断乘以 2 直至溢出回绕为负，此时的负值即最小值，
 * 最小值减 1（回绕）即最大值。浮点类型可不断加倍，最后一次加倍前的
 * 有限值即最大值的近似。
 */
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    /* 方法一：打印标准头文件中的范围宏 */
    printf("--- from standard headers ---\n");
    printf("char: %d .. %d\n", CHAR_MIN, CHAR_MAX);
    printf("signed char: %d .. %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: 0 .. %u\n", UCHAR_MAX);
    printf("short: %d .. %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short: 0 .. %u\n", USHRT_MAX);
    printf("int: %d .. %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: 0 .. %u\n", UINT_MAX);
    printf("long: %ld .. %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long: 0 .. %lu\n", ULONG_MAX);
    printf("float: %e .. %e\n", FLT_MIN, FLT_MAX);
    printf("double: %e .. %e\n", DBL_MIN, DBL_MAX);

    /* 方法二：直接计算 */
    printf("--- by direct computation ---\n");

    {
        unsigned char uc = (unsigned char)-1;
        unsigned short us = (unsigned short)-1;
        unsigned int ui = -1;
        unsigned long ul = -1UL;
        printf("unsigned char: 0 .. %u\n", uc);
        printf("unsigned short: 0 .. %u\n", us);
        printf("unsigned int: 0 .. %u\n", ui);
        printf("unsigned long: 0 .. %lu\n", ul);
    }

    {
        signed char c = 1;
        short s = 1;
        int i = 1;
        long l = 1L;
        while (c > 0)
            c = (signed char)(c * 2);
        while (s > 0)
            s = (short)(s * 2);
        while (i > 0)
            i = i * 2;
        while (l > 0)
            l = l * 2;
        printf("char: %d .. %d\n", c, (signed char)(c - 1));
        printf("short: %d .. %d\n", s, (short)(s - 1));
        printf("int: %d .. %d\n", i, i - 1);
        printf("long: %ld .. %ld\n", l, l - 1);
    }

    {
        float f = 1.0f, prevf;
        double d = 1.0, prevd;
        do {
            prevf = f;
            f = f * 2.0f;
        } while (f * 2.0f != f);
        do {
            prevd = d;
            d = d * 2.0;
        } while (d * 2.0 != d);
        printf("float max (approx): %e\n", prevf);
        printf("double max (approx): %e\n", prevd);
    }
    return 0;
}
