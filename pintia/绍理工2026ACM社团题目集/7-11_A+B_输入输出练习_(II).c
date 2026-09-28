/*
  @pintia psid=2101637166657720320 pid=2101637166938738698 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: A+B 输入输出练习 (II)
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166938738698
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", a + b);
    }
    

    return 0;
}
// @pintia code=end