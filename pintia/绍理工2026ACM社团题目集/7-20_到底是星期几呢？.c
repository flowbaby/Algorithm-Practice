/*
  @pintia psid=2101637166657720320 pid=2101637166942932994 compiler=GCC
  ProblemSet: 绍理工2026ACM社团题目集
  Title: 到底是星期几呢？
  https://pintia.cn/problem-sets/2101637166657720320/exam/problems/type/7?problemSetProblemId=2101637166942932994
*/
// @pintia code=start
#include <stdio.h>

int isLeap(int y);

int main()
{
    int N;
    int mm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int y, m, d;
        int sum_days = 0;
        scanf("%d %d %d", &y, &m, &d);
        for (int j = 1; j < y; j++) {
            if (isLeap(j)) {
                sum_days += 366;
            } else {
                sum_days += 365;
            }
        }
        for (int j = 1; j < m; j++) {
            sum_days += mm[j - 1];
            if (isLeap(y)&&j==2) {
                sum_days++;
            }
        }
        for (int j = 1; j <= d; j++) {
            sum_days++;
        }
        int week = sum_days % 7;
        week = week == 0 ? 7 : week;

        printf("%d\n", week);
    }

    return 0;
}

int isLeap(int y)
{
    int flag = 1;
    if (y % 400 == 0) {
        flag = 1;
    } else if (y % 100 == 0) {
        flag = 0;
    } else if (y % 4 == 0) {
        flag = 1;
    } else {
        flag = 0;
    }
    return flag;
}
// @pintia code=end