/*
  @pintia psid=2102248980422123520 pid=2102248980443095042 compiler=GCC
  ProblemSet: 1.分支结构(if / switch)
  Title: 计算平均成绩统计不及格人数
  https://pintia.cn/problem-sets/2102248980422123520/exam/problems/type/7?problemSetProblemId=2102248980443095042
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int N;
    int average = 0;
    int sum = 0;
    int count = 0;
    scanf("%d", &N);
    int n = N;
    while (N > 0) {
        int grade;
        scanf("%d", &grade);
        if (grade < 60) {
            count++;
        }
        sum = sum + grade;
        N--;
    }
    if (n > 0)
        average = sum / n;
    printf("average = %d\n", average);
    printf("count = %d", count);
    return 0;
}
// @pintia code=end