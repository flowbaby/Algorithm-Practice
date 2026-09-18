// 假如我国国民生产总值的年增长率为7%，计算10年后我国国民生产总值与现在相比增长多少百分比。计算公式为：p=(1+r)^n

// 其中：r为年增长率，n为年数，p为与现在相比的倍数
#include <stdio.h>
#include <math.h>
int main()
{
    double r = 0.07;
    int n = 10;
    double p = pow(1 + r, n);
    printf("%f", p);
    return 0;
}