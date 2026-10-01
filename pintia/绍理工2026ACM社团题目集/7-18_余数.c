/*
  @pintia psid=2101637166657720320 pid=2101637166942932992 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: 余数
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166942932992
*/
// @pintia code=start
#include <stdio.h>
#include <math.h>

int main()
{
    int a;
    while (scanf("%d", &a) == 1) {
        printf("%d\n", (int)round(a/2.0)+1);
    }

    return 0;
}
// @pintia code=end