/*
  @pintia psid=2102249312065753088 pid=2102249312090918914 compiler=GCC
  ProblemSet: 2.循环结构(for / while)
  Title: 奇偶个数
  https://pintia.cn/problem-sets/2102249312065753088/exam/problems/type/7?problemSetProblemId=2102249312090918914
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int input;
    scanf("%d", &input);
    int odd = 0;
    int even = 0;
    while (input != -1) {
        if (input % 2 == 0) {
            even++;
        } else {
            odd++;
        }
        scanf("%d", &input);
    }
    printf("%d,%d", odd, even);
    return 0;
}
// @pintia code=end