/*
  @pintia psid=2112024321886732288 pid=2112024322071298056 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: 昨日重现—这是一道经典题
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298056
*/
// @pintia code=start
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void mprint(int, char);

int main()
{
    int n;
    scanf("%d", &n);
    int d;
    for (int i = 1; i <= n * 2 - 1; i++) {
        d = n - 1 - abs(i - n);
        if (d == 0) {
            mprint(n * 3, '*');
            mprint(n, ' ');
            mprint(n * 3, '*');
            printf("\n");
        } else if (d >= 1 && d <= n / 2 - 1) {
            mprint(d, ' ');
            mprint(1, '*');
            mprint(n * 3 - 2, ' ');
            mprint(1, '*');
            mprint(n - d * 2, ' ');
            mprint(1, '*');
            mprint(n * 3 - 2, ' ');
            mprint(1, '*');
            printf("\n");
        } else if (d >= n / 2 - 1 && d <= n - 1) {
            mprint(d, ' ');
            mprint(1, '*');
            mprint(n * 6 - 2 - (d - n / 2) * 2, ' ');
            mprint(1, '*');
            printf("\n");
        }
    }

    return 0;
}

void mprint(int n, char ch)
{
    for (int i = 0; i < n; i++) {
        printf("%c", ch);
    }
}

// @pintia code=end