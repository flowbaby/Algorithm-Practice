/*
  @pintia psid=2112024660870381568 pid=2112024661063319554 compiler=GCC
  ProblemSet: 2022-2023 学年秋学期程序设计基础联考第一场
  Title: 小y爱运动
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319554
*/
// @pintia code=start
#include <stdio.h>
int main()
{
    int summ = 0;
    for (int i = 0; i < 3; i++) {
        int h1, m1, h2, m2;
        scanf("%d %d %d %d", &h1, &m1, &h2, &m2);
        summ = summ + (h2 - h1) * 60 + m2 - m1;
    }
    printf("%d %d\n", summ / 60, summ % 60);
    printf(summ / 60 >= 4 ? "YES" : "NO");

    return 0;
}

// @pintia code=end