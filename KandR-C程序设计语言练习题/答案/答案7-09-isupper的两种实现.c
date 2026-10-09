/*
 * 答案7-09 isupper的两种实现
 *
 * 提示：isupper 这类字符分类函数可以在"节省空间"与"节省时间"两种目标间权衡。
 * 一、节省时间的实现：采用查表法。预先建立一张 256 项的静态表（初始化时按 ASCII 规则填好 0/1），
 *    运行时只需一次下标访问加一次与运算，无需任何比较和分支，时间确定且极小；
 *    若用宏定义封装查表，还能免去函数调用开销。代价是表要占 256 字节空间。
 * 二、节省空间的实现：采用表达式函数。用两次比较判断 c 是否落在 'A' 与 'Z' 之间，
 *    代码只有几字节，不占用数据空间；代价是每次调用都要执行比较与分支，运行略慢。
 *    写成真正的函数（而非宏）可避免重复展开导致代码膨胀，这也是"节省空间"的经典做法。
 * 实际标准库常两者结合：头文件中用宏定义查表，库中同时提供函数版本供取地址使用。
 * 以下演示代码同时给出两种实现，并用 clock() 粗略比较在大量调用下的速度差异。
 */
#include <stdio.h>
#include <time.h>

/* 方式一：函数实现（节省空间：无数据表，代码紧凑） */
int isupper_func(int c)
{
    return c >= 'A' && c <= 'Z';
}

/* 方式二：查表实现（节省时间：一次索引即可，无比较分支） */
static char upper_table[256];

static void init_upper_table(void)
{
    int c;
    for (c = 0; c < 256; c++)
        upper_table[c] = (c >= 'A' && c <= 'Z');
}

#define isupper_tab(c) (upper_table[(unsigned char)(c)] != 0)

#define NTESTS 20000000L

int main(void)
{
    long i, count;
    clock_t start, end;

    init_upper_table();

    count = 0;
    start = clock();
    for (i = 0; i < NTESTS; i++)
        count += isupper_func((int)(i & 255));
    end = clock();
    printf("函数实现 : %ld 个时钟单位, count = %ld\n", (long)(end - start), count);

    count = 0;
    start = clock();
    for (i = 0; i < NTESTS; i++)
        count += isupper_tab((int)(i & 255));
    end = clock();
    printf("查表实现 : %ld 个时钟单位, count = %ld\n", (long)(end - start), count);

    return 0;
}
