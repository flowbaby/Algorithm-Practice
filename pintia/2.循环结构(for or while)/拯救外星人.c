/*
  @pintia psid=2102249312065753088 pid=2102249312090918913 compiler=GCC
  ProblemSet: 2.循环结构(for / while)
  Title: 拯救外星人
  https://pintia.cn/problem-sets/2102249312065753088/exam/problems/type/7?problemSetProblemId=2102249312090918913
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int a, b;
    int sum = 1;
    scanf("%d %d", &a, &b);
    for (int i = 1; i <= a + b; i++) {
        sum = sum * i;
    }
    printf("%d", sum);
    return 0;
}
// @pintia code=end