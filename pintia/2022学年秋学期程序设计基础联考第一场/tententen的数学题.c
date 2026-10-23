/*
  @pintia psid=2112024660870381568 pid=2112024661063319560 compiler=GCC
  ProblemSet: 2022学年秋学期程序设计基础联考第一场
  Title: tententen的数学题
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319560
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                if ((i + j) % m == 0 && (j + k) % m == 0 && (i + k) % m == 0) {
                    cnt++;
                }
            }
        }
    }
    printf("%d", cnt);

    return 0;
}
// @pintia code=end