/*
  @pintia psid=2115441217247838208 pid=2115441217461764097 compiler=GCC
  ProblemSet: 2026年杭州师范大学程序设计基础课程多校联考第一场（补）
  Title: 皮蛋买汉堡
  https://pintia.cn/problem-sets/2115441217247838208/exam/problems/type/7?problemSetProblemId=2115441217461764097
*/
// @pintia code=start
#include <stdio.h>
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int sum = 0;
    sum = sum + n / m;
    if (n % m > 0) {
        sum++;
    }
    printf("%d", sum);
    return 0;
}
// @pintia code=end