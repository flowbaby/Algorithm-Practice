/*
  @pintia psid=2112024660870381568 pid=2112024661063319559 compiler=GCC
  ProblemSet: 2022学年秋学期程序设计基础联考第一场
  Title: 求函数值
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319559
*/
// @pintia code=start
#include <stdio.h>
double qur(double, double, double, double, double, double);

int main()
{
    double a3, a2, a1, a0;
    double a, b;
    scanf("%lf %lf %lf %lf", &a3, &a2, &a1, &a0);
    scanf(" %lf %lf", &a, &b);
    double ret = qur(a3, a2, a1, a0, a, b);
    printf("%.2lf", ret);
    return 0;
}

double qur(double a3, double a2, double a1, double a0, double a, double b)
{
    double x = (a + b) / 2;
    double fx = ((a3 * x + a2) * x + a1) * x + a0;
    double fa = ((a3 * a + a2) * a + a1) * a + a0;
    if (b - a < 0.001 || fx == 0) {
        return (a + b) / 2;
    } else {
        return fx * fa > 0 ? qur(a3, a2, a1, a0, x, b) : qur(a3, a2, a1, a0, a, x);
    }
}

// @pintia code=end