// 计算分段函数，求y的值

// 2x   x<=-10

// 2+x  -10<x<=0

// x-2  0<x<=10

// x/10 x>10
#include <stdio.h>

int main()
{
    double x, y;
    scanf("%lf", &x);
    y = x / 10;
    if (x <= -10)
        y = 2 * x;
    else if (x <= 0)
        y = 2 + x;
    else if (x <= 10)
        y = x - 2;
    printf("y=%.2f", y);
    return 0;
}