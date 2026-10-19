/*
  @pintia psid=2112024321886732288 pid=2112024322071298049 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: 这是一道难题
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298049
*/
// @pintia code=start
#include <stdio.h>
int main()
{
    int cnt = 0;
    int x;
    scanf("%d", &x);
    if (x == 0)
        cnt++;
    while (x > 0) {
        if (x % 10 % 2 == 0) {
            cnt++;
        }
        x /= 10;
    }
    printf("%d\n", cnt);
    return 0;
}
// @pintia code=end