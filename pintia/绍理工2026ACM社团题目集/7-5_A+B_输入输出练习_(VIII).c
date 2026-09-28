/*
  @pintia psid=2101637166657720320 pid=2101637166938738692 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: A+B 输入输出练习 (VIII)
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166938738692
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int T, n;
    scanf("%d", &T);
    int sum = 0;
    int x = 0;

    for (int i = 0; i < T; i++) {
        scanf("%d", &n);
        for (int j = 0; j < n; j++) {
            scanf("%d", &x);
            sum = sum + x;
            x = 0;
        }
        n = 0;

        printf("%d\n", sum);
        if (i != T - 1) {
            printf("\n");
        }
        sum = 0;
    }

    return 0;
}
// @pintia code=end