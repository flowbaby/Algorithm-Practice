/*
  @pintia psid=2112024660870381568 pid=2112024661063319558 compiler=GCC
  ProblemSet: 2022学年秋学期程序设计基础联考第一场
  Title: 线段数
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319558
*/
// @pintia code=start
#include <stdio.h>

double an(int);

int main()
{
    double eps;
    scanf("%lf", &eps);
    double sum = 0;
    int i=1;
    for ( i = 1; !(an(i) > eps && an(i + 1) <= eps); i++) {
        sum += an(i);
    }
    sum += an(i);
    sum += an(i + 1);
    printf("%.6lf\n", sum);
    return 0;
}

double an(int i)
{
    return 1.0 / i / (2 * i - 1);
}
// @pintia code=end
