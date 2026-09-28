/*
  @pintia psid=2101637166657720320 pid=2101637166938738697 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: A+B 输入输出练习 (III)
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166938738697
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    while (a + b != 0) {

        printf("%d\n", a + b);
        scanf("%d %d", &a, &b);
    }

    return 0;
}
// @pintia code=end