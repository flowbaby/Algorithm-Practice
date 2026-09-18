// 从键盘输入一个数，判断奇偶性，偶数输出2，奇数输出1。
#include <stdio.h>

int main()
{
    int a;
    scanf("%d", &a);
    if (a % 2 == 0)
        printf("2");
    else
        printf("1");
    return 0;
}