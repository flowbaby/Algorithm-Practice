/*
  @pintia psid=2101637166657720320 pid=2101637166938738695 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: A+B 输入输出练习 (V)
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166938738695
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int T, n;
    int sum = 0;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &n);
        for (int j = 0; j < n; j++)
        {
            int x;
            scanf("%d", &x);
            sum = sum + x;
        }
        printf("%d\n", sum);
        sum = 0;
        n = 0;
    }
    

    return 0;
}
// @pintia code=end