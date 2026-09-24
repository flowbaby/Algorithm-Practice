/*
  @pintia psid=2102249416592003072 pid=2102249416612974592 compiler=GCC
  ProblemSet: 3.一维数组
  Title: 整数进制转换
  https://pintia.cn/problem-sets/2102249416592003072/exam/problems/type/7?problemSetProblemId=2102249416612974592
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int posn, n;
    int x;
    long long ret = 0;
    long long mask = 1;
    scanf("%d %d", &posn, &n);
    while (posn > 0)
    {
        x = posn % n;
        ret = ret + x * mask;
        mask *= 10;
        posn /= n;
        // printf("posn=%d,ret=%lld\n",posn,ret;
    }
    printf("%lld\n", ret);
    return 0;
}
// @pintia code=end