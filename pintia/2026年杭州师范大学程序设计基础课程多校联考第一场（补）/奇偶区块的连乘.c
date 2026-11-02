/*
  @pintia psid=2115441217247838208 pid=2115441217461764102 compiler=GCC
  ProblemSet: 2026年杭州师范大学程序设计基础课程多校联考第一场（补）
  Title: 奇偶区块的连乘
  https://pintia.cn/problem-sets/2115441217247838208/exam/problems/type/7?problemSetProblemId=2115441217461764102
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    long long N;
    scanf("%lld", &N);
    int attr = N % 2;
    int temp = 0;
    int sum = 1;
    while (N > 0) {
        int d = N % 10;
        if (attr == d % 2) {
            temp += d;
        } else {
            // printf("%d *", temp);
            sum = sum * temp;
            temp = d;
            attr = !attr;
        }
        // printf("\n");
        N = N / 10;
    }
    printf("%d", sum*temp);
    return 0;
}
// @pintia code=end