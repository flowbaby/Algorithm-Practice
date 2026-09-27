/*
  @pintia psid=2102249726483959808 pid=2102249726504931328 compiler=GCC
  ProblemSet: 5.函数：素数、GCD、LCM、自定义函数
  Title: 素数求和。
  https://pintia.cn/problem-sets/2102249726483959808/exam/problems/type/7?problemSetProblemId=2102249726504931328
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int m, n;
    int flag = 1;
    int sum = 0;
    int count = 0;

    scanf("%d %d", &m, &n);
    int x = m;
    if (m == 1) {
        m = 2;
    }
    for (int i = m; i <= n; i++) {
        flag = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            sum = sum + i;
            count++;
        }
    }
    printf("%d和%d之间有%d个素数，这些素数的和是%d。", x, n, count, sum);
    return 0;
}

// @pintia code=end