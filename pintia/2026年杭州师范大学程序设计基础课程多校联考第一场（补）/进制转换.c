/*
  @pintia psid=2115441217247838208 pid=2115441217461764101 compiler=GCC
  ProblemSet: 2026年杭州师范大学程序设计基础课程多校联考第一场（补）
  Title: 进制转换
  https://pintia.cn/problem-sets/2115441217247838208/exam/problems/type/7?problemSetProblemId=2115441217461764101
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int bin;
        scanf("%4d", &bin);
        if (bin == 1010) {
            cnt++;
        }
    }
    printf("%d", cnt);
    return 0;
}
// @pintia code=end