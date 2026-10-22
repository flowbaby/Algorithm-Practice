// 从键盘输入一批正整数（以零或负数为结束标志），判断并输出每个奇数及所有奇数的和。
#include <stdio.h>

int main()
{
    int x;
    int sum = 0;
    do {
        scanf("%d", &x);
        if (x % 2 == 1) {
            printf("奇数：%d\n", x);
            sum += x;
        }

    } while (x > 0);
    printf("奇数和：%d\n", sum);

    return 0;
}