/*
  @pintia psid=2101637166657720320 pid=2101637166938738694 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: A+B 输入输出练习 (VI)
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166938738694
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int n;

    while (scanf("%d", &n) != EOF) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            int x = 0;
            scanf("%d", &x);
            sum = sum + x;
        }
        printf("%d\n\n", sum);
    }

    return 0;
}
// @pintia code=end