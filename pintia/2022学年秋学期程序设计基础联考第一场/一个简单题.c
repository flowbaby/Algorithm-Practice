/*
  @pintia psid=2112024660870381568 pid=2112024661063319557 compiler=GCC
  ProblemSet: 2022-2023 学年秋学期程序设计基础联考第一场
  Title: 一个简单题
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319557
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    if (a == 0) {
        printf("1\n");
    } else {
        printf("%d\n", a + b * 2 + 1);
    }

    return 0;
}
// @pintia code=end
