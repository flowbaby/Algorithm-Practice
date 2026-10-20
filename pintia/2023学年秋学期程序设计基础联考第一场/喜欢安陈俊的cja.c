/*
  @pintia psid=2112024321886732288 pid=2112024322071298057 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: 喜欢安陈俊的cja
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298057
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int x, y, q, pos, t;
        scanf("%d %d %d %d %d", &x, &y, &q, &pos, &t);
        int teacher_watch_time = (pos - 1) * t;
        int norm_ac;
        int acj_ac;
        if (teacher_watch_time > q) {
            // 算出解题时间
            norm_ac = teacher_watch_time / x;
            acj_ac = (teacher_watch_time-q) / y;
            if (acj_ac > norm_ac) {
                printf("Yes\n");
            } else if (acj_ac == norm_ac) {
                printf("So So\n");
            } else {
                printf("No\n");
            }

        } else {
            printf("No\n");
        }
    }

    return 0;
}
// @pintia code=end