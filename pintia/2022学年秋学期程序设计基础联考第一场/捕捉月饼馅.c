/*
  @pintia psid=2112024660870381568 pid=2112024661063319556 compiler=GCC
  ProblemSet: 2022-2023 学年秋学期程序设计基础联考第一场
  Title: 捕捉月饼馅
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319556
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    char ch;
    scanf("%c", &ch);
    int a, b, c, d, e;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    int flag = ch == 'p' ? 1 : 0;
    int mul = a % 10;
    mul = mul * (b % 10) % 10;
    mul = mul * (c % 10) % 10;
    mul = mul * (d % 10) % 10;
    if (flag && mul == e % 10) {
        printf("hihihi,yaquyuebing,hihihi %d\n", mul);
    } else {
        printf("meidechi,555 %d\n", mul);
    }

    return 0;
}
// @pintia code=end
