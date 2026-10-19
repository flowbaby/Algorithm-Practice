/*
  @pintia psid=2112024321886732288 pid=2112024322071298051 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: 这道题只有天赋怪能过
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298051
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if (a + b + c < 1000 && a % 12 == 0 && a - b > b - c) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}
// @pintia code=end