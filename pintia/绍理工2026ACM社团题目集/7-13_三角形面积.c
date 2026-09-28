/*
  @pintia psid=2101637166657720320 pid=2101637166938738700 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: 三角形面积
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166938738700
*/
// @pintia code=start
#include <math.h>
#include <stdio.h>

int main()
{
    int a, b, c;

    while (scanf("%d %d %d", &a, &b, &c) == 3) {
        double S = 0.5 * a * b * sin(c * 3.1415926 / 180);
        printf("%.3f\n", S);
        S = 0;
    }

    return 0;
}
// @pintia code=end