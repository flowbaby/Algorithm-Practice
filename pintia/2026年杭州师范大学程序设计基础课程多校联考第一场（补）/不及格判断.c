/*
  @pintia psid=2115441217247838208 pid=2115441217461764098 compiler=GCC
  ProblemSet: 2026年杭州师范大学程序设计基础课程多校联考第一场（补）
  Title: 不及格判断
  https://pintia.cn/problem-sets/2115441217247838208/exam/problems/type/7?problemSetProblemId=2115441217461764098
*/
// @pintia code=start
#include <stdio.h>
int main()
{
    int a1, a2, a3;
    scanf("%d %d %d", &a1, &a2, &a3);
    if (a1 < 60 && a2 > 59 && a3 > 59 || a1 > 59 && a2 < 60 && a3 > 59 || a1 > 59 && a2 > 59 && a3 < 60) {
        printf("You are not our friends");
    } else {
        printf("You are not our enemy either");
    }
    return 0;
}
// @pintia code=end