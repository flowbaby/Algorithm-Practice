/*
  @pintia psid=2102249312065753088 pid=2102249312086724609 compiler=GCC
  ProblemSet: 2.循环结构(for / while)
  Title: 打印矩形图案
  https://pintia.cn/problem-sets/2102249312065753088/exam/problems/type/7?problemSetProblemId=2102249312086724609
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
// @pintia code=end