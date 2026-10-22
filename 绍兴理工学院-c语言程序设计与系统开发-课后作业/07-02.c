// 输入一个实数x，计算并输出下式的和，直到最后一项的绝对值小于0.00001，计算结果保留4位小数。

// s=1+x+x2/2!+x3/3!+x4/4!+......(x2即表示x的平方，x3即表示x的3次方，以此类推)
#include <math.h>
#include <stdio.h>

int main()
{
    // 相邻项递推
    double x;
    double s = 0;
    double an = 1;
    scanf("%lf", &x);
    for (int i = 1; fabs(an) > 0.00001; i++) {
        s += an;
        an *= x / i;
    }
    printf("%.4lf\n", s);
    return 0;
}
