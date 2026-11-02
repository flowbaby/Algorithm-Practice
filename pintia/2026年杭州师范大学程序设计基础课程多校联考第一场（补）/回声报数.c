/*
  @pintia psid=2115441217247838208 pid=2115441217461764103 compiler=GCC
  ProblemSet: 2026年杭州师范大学程序设计基础课程多校联考第一场（补）
  Title: 回声报数
  https://pintia.cn/problem-sets/2115441217247838208/exam/problems/type/7?problemSetProblemId=2115441217461764103
*/
// @pintia code=start
#include <stdio.h>

int is_contain3(int x);
int main()
{
    int N;
    scanf("%d", &N);
    int x = 1;
    int ban_cnt = 0;
    int out_time = 0;
    while (out_time < N) {
        if (x % 3 == 0 || is_contain3(x)) {
            ban_cnt++;
        } else {
            if (ban_cnt >= 2) {
                out_time += 2;
            } else {
                out_time++;
            }
            ban_cnt = 0;
        }
        x++;
        // printf("x=%d,第%d次,屏蔽次数%d\n", x, out_time, ban_cnt);
    }
    printf("%d", x-1);
    return 0;
}
int is_contain3(int x)
{
    while (x > 0) {
        int d = x % 10;
        if (d == 3) {
            return 1;
        }
        x = x / 10;
    }
    return 0;
}
// @pintia code=end