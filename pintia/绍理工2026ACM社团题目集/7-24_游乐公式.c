/*
  @pintia psid=2101637166657720320 pid=2101637166942932998 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: 游乐公式
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166942932998
*/
// @pintia code=start
#include <math.h>
#include <stdio.h>

int fact(int x);
// TODO: 求第x个素数的值
int prime(int x);

int main()
{
    int n, m;
    int sum;
    while (scanf("%d %d", n, m) == 2) {
        n = m = sum = 0;

        for (int a = 1; a <= n; a++) {
            sum += fact((int)pow(a, prime(m) - 1)) % a;
        }

        printf("%d", sum);
    }

    return 0;
}

// 求阶乘
int fact(int x)
{
    return x > 0 ? fact(x - 1) : 1;
}
// @pintia code=end