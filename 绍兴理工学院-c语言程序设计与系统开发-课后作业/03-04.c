// 从键盘输入一个小于1000的正整数，要求输出它的平方根（如平方根不是整数，则输出其整数部分）。要求在输入数据后先对其进行检查是否小于1000，若不是，则要求重新输入。
#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    scanf("%d", &n);
    while (n >= 1000 || n < 1)
    {
        printf("请重新输入：");
        scanf("%d", &n);
    }
    printf("%d", (int)sqrt(n));

    return 0;
}