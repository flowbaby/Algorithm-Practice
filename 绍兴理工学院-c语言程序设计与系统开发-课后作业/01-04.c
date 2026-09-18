// 求ax^2+bx+c=0方程的实数根。（b^2-4ac>=0）
#include <math.h>
#include <stdio.h>
int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if (a == 0)
    {
        printf("不是一元二次方程\n");
        return 0;
    }
    double delta = b*b - 4*a*c;
    if (delta == 0)
    {
        double x = (-b) / (2.0 * a);
        printf("%f", x);
    }
    else if (delta > 0)
    {
        double x1 = (-b + sqrt(delta)) / (2.0 * a);
        double x2 = (-b - sqrt(delta)) / (2.0 * a);
        printf("%f %f", x1, x2);
    }
    else
    {
        printf("无实数根");
    }
    return 0;
}
