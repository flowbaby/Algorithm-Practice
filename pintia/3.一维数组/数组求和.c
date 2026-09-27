/*
  @pintia psid=2102249416592003072 pid=2102249416612974596 compiler=GCC
  ProblemSet: 3.一维数组
  Title: 数组求和
  https://pintia.cn/problem-sets/2102249416592003072/exam/problems/type/7?problemSetProblemId=2102249416612974596
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int flag = 1;
    int x;
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        scanf("%d", &x);
        if (flag) {
            sum = sum + x * 2;
        } else {
            sum = sum + x + 2;
        }
        flag = !flag;
    }
    printf("sum = %d", sum);
    return 0;
}
// @pintia code=end