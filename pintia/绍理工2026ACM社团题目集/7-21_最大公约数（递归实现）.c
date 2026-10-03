/*
  @pintia psid=2101637166657720320 pid=2101637166942932995 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: 最大公约数（递归实现）
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166942932995
*/
// @pintia code=start
#include <stdio.h>

int gcd(int, int);

int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        printf("%d\n", gcd(n, m));
    }
    return 0;
}

int gcd(int a, int b)
{
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// @pintia code=end