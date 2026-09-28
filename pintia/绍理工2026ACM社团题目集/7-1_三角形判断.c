/*
  @pintia psid=2101637166657720320 pid=2101637166938738688 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: 三角形判断
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166938738688
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if (a+b>c&&a+c>b&&b+c>a)
    {
        printf("YES");
    }else{
        printf("NO");
    }
    

    return 0;
}
// @pintia code=end