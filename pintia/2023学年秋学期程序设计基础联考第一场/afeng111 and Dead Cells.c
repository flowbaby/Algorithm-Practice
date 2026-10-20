/*
  @pintia psid=2112024321886732288 pid=2112024322071298058 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: afeng111 and Dead Cells
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298058
*/
// @pintia code=start
#include <stdio.h>


int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        long long hpa, hpb;
        long long x, y, d, cnt;
        scanf("%lld %lld %lld %lld %lld %lld", &hpa, &hpb, &x, &y, &d, &cnt);
        long long max = hpa;
        int flag = 0;

        // 血量安全跳过
        while (hpa > 0) {
            // printf("玩家血量%d,boss血量%d\n", hpa, hpb);

            // 优先斩杀
            if (hpb - x <= 0) {
                hpb -= x;
                flag = 1;
                break;
            }
            // 一次跳过所有安全的连续攻击
            if (hpa > y) {
                long long times = (hpa - 1) / y;
                hpa -= times * y;
                hpb -= times * x;

                if (hpb <= 0) {
                    flag = 1;
                    break;
                }
                continue;
            }
            // 濒死回血
            else if (d > y && cnt > 0) {
                hpa += d;
                if (hpa > max) {
                    hpa = max;
                }
                cnt--;
            }
            // 优先攻击
            else {
                hpb -= x;
                if (hpb <= 0) {
                    flag = 1;
                    break;
                }
            }
            hpa -= y;
        }
        if (flag) {
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }

    return 0;
}
// @pintia code=end
