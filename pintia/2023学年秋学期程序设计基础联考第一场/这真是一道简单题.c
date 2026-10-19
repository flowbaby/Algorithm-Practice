/*
  @pintia psid=2112024321886732288 pid=2112024322071298050 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: 这真是一道简单题
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298050
*/
// @pintia code=start
#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int fee = 0;
    int bare = 8;
    if (n <= 1) {
    } else if (n <= 5) {
        fee = bare * n;
    } else {
        fee = bare * 5;
        n -= 5;
        while (n > 0) {
            bare++;
            fee = fee + bare;
            n--;
        }
    }
    if (fee > 300) {
        fee = 300;
    }
    printf("%d", fee);

    return 0;
}
// @pintia code=end