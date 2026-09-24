/*
  @pintia psid=2102249312065753088 pid=2102249312090918912 compiler=GCC
  ProblemSet: 2.循环结构(for / while)
  Title: 国王的金币
  https://pintia.cn/problem-sets/2102249312065753088/exam/problems/type/7?problemSetProblemId=2102249312090918912
*/
// @pintia code=start
#include <math.h>
#include <stdio.h>
int main()
{
    int n;
    int coin = 0;
    int day = 0;
    int sum = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {

        if (day++ == coin) {
            day = 1;
            coin++;
        }
        sum = sum + coin;
    }
    printf("%d", sum);
    return 0;
}
// @pintia code=end