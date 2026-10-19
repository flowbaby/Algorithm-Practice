/*
  @pintia psid=2112024321886732288 pid=2112024322071298052 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: 神奇台灯
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298052
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int a, m;
    scanf("%d %d", &a, &m);
    int real = 0;
    real = m;
    while (!(real >= 0 && real <= a)) {
        real -= a;
        real--;
    }
    printf("%d", real);

    return 0;
}
// @pintia code=end