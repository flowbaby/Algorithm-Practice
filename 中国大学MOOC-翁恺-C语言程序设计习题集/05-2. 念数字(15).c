// 时间限制
// 400 ms
// 内存限制
// 65536 kB
// 代码长度限制
// 8000 B
// 判题程序
// Standard
// 作者
// 翁恺（浙江大学）
// 输入一个整数，输出每个数字对应的拼音。当整数为负数时，先输出“fu”字。十个数字对应的拼音如下：

// 0: ling
// 1: yi
// 2: er
// 3: san
// 4: si
// 5: wu
// 6: liu
// 7: qi
// 8: ba
// 9: jiu
// 输入格式：

// 输入在一行中给出一个整数，如：1234。

// 提示：整数包括负数、零和正数。

// 输出格式：

// 在一行中输出这个整数对应的拼音，每个数字的拼音之间用空格分开，行末没有最后的空格。如yi er san si。

// 输入样例：
// -600
// 输出样例：
// fu liu ling ling
#include <stdio.h>

int main()
{
    int num = 0;
    int d = 0;
    int mask = 1;
    scanf("%d", &num);
    // num = 123;
    if (num < 0) {
        printf("fu ");
        num = -num;
    }

    int x = num;

    // 求num的长度
    while (x > 9) {
        mask *= 10;
        x /= 10;
    }

    // 正序切分
    while (mask > 0) {

        // 123 / 100 -> 1
        // 123 % 100 -> 23
        // 100 / 10  -> 10
        // 23 / 10 -> 2
        // 23 % 10 -> 3
        // 10 / 10 -> 1
        // 3 / 1  -> 3
        // 3 % 1  -> 0
        // 1 / 10 -> 0

        d = num / mask;

        if (d == 0)
            printf("ling");
        else if (d == 1)
            printf("yi");
        else if (d == 2)
            printf("er");
        else if (d == 3)
            printf("san");
        else if (d == 4)
            printf("si");
        else if (d == 5)
            printf("wu");
        else if (d == 6)
            printf("liu");
        else if (d == 7)
            printf("qi");
        else if (d == 8)
            printf("ba");
        else if (d == 9)
            printf("jiu");
        if (mask > 9) {
            printf(" ");
        }
        num = num % mask;
        mask /= 10;
    }
    return 0;
}