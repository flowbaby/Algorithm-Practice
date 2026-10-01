/*
  @pintia psid=2101637166657720320 pid=2101637166938738704 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: 计算银行存款的本息
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166938738704
*/
// @pintia code=start
#include <stdio.h>
#include <math.h>

int main()
{
    int money, year;
    double rate;
    scanf("%d %d %lf", &money, &year, &rate);
    double sum = 0;
    sum = money * pow(1 + rate, year);
    printf("sum = %.2f", sum);
    return 0;
}
// @pintia code=end