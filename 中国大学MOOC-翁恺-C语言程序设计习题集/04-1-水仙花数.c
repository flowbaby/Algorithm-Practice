// 时间限制
// 2000 ms
// 内存限制
// 65536 kB
// 代码长度限制
// 8000 B
// 判题程序
// Standard
// 作者
// 徐镜春（浙江大学）
// 水仙花数是指一个N位正整数（N>=3），它的每个位上的数字的N次幂之和等于它本身。例如：153 = 1^3 + 5^3+ 3^3。本题要求编写程序,计算所有N位水仙花数。

// 输入格式：

// 输入在一行中给出一个正整数N（3<=N<=7）。

// 输出格式：

// 按递增顺序输出所有N位水仙花数，每个数字占一行。

// 输入样例：
// 3
// 输出样例：
// 153
// 370
// 371
// 407
#include <stdio.h>
int power1(int base, int exp)
{
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main()
{
    int input;
    int cur = 0;
    int num = 0;
    int sum = 0;

    scanf("%d", &input);

    for (num = power1(10, input - 1); num < power1(10, input); num++) {
        int i = num;
        sum = 0;
        while (i > 0) {
            cur = i % 10;
            sum += power1(cur, input);
            i /= 10;
        }
        if (sum == num) {
            printf("%d\n", num);
        }
    }

    return 0;
}
