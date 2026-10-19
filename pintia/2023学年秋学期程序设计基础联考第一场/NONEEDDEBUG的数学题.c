/*
  @pintia psid=2112024321886732288 pid=2112024322071298053 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: NONEEDDEBUG的数学题
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298053
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int n;
    int mul = 0;
    int answer = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = j + 1; i + j + k <= n; k++) {
                if (i + j + k == n
                    && i * i + j * j == k * k) {
                    mul = i * j * k;
                    answer++;
                }
            }
        }
    }
    if (answer == 1) {
        printf("%d", mul);
    } else if (answer > 1) {
        printf("Many %d", answer);
    } else {
        printf("No Joyfine");
    }

    return 0;
}
// @pintia code=end