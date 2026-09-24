/*
  @pintia psid=2102248980422123520 pid=2102248980443095040 compiler=GCC
  ProblemSet: 1.分支结构(if / switch)
  Title: 成绩等级
  https://pintia.cn/problem-sets/2102248980422123520/exam/problems/type/7?problemSetProblemId=2102248980443095040
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    double input;
    char ch = 'E';
    scanf("%lf", &input);
    switch ((int)input / 10) {
    case 10:
    case 9:
        ch = 'A';
        break;
    case 8:
        ch = 'B';
        break;
    case 7:
        ch = 'C';
        break;
    case 6:
        ch = 'D';
        break;
    }
    printf("%c", ch);
    return 0;
}
// @pintia code=end