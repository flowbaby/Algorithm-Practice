// 输出所有的三位水仙花数。所谓“水仙花数”是指一个3位数，其各位数字立方和等于该数本身。例如，153是一个水仙花数。因为153=1*1*1+5*5*5+3*3*3。
#include <stdio.h>

int main()
{
    for (int i = 100; i < 1000; i++) {
        int a = i / 100;
        int b = i / 10 % 10;
        int c = i % 10;
        if (a * a * a + b * b * b + c * c * c == i) {
            printf("%d\n", i);
        }
    }

    return 0;
}