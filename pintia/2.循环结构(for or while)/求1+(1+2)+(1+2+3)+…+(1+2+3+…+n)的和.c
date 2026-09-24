/*
  @pintia psid=2102249312065753088 pid=2102249312086724608 compiler=GCC
  ProblemSet: 2.循环结构(for / while)
  Title: 求1+(1+2)+(1+2+3)+…+(1+2+3+…+n)的和
  https://pintia.cn/problem-sets/2102249312065753088/exam/problems/type/7?problemSetProblemId=2102249312086724608
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            sum += j;
        }
    }
    printf("sum = %d", sum);

    return 0;
}
// @pintia code=end