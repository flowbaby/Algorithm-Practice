/*
  @pintia psid=2112024660870381568 pid=2112024661063319561 compiler=GCC
  ProblemSet: 2022学年秋学期程序设计基础联考第一场
  Title: stff577&Sigma
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319561
*/
// @pintia code=start
#include <stdio.h>
#include <stdlib.h>

void mprint(int, char);

int main()
{
    int n;
    scanf("%d", &n);
    int mid = n;
    for (int i = 1; i <= n * 2 - 1; i++) {
        int d = mid - 1 - abs(i - mid);
        if (d == 0) {
            mprint(n * 3, '*');
        } else if (d >= 1 && d <= n / 2 - 1) {
            mprint(d, ' ');
            mprint(1, '*');
            mprint(n * 3 - 2 * d - 2, ' ');
            mprint(1, '*');
        } else {
            mprint(d, ' ');
            mprint(1, '*');
        }
        printf("\n");
    }

    return 0;
}

void mprint(int i, char c)
{
    for (int j = 0; j < i; j++) {
        printf("%c", c);
    }
}
// @pintia code=end