/*
  @pintia psid=2115441217247838208 pid=2115441217461764099 compiler=GCC
  ProblemSet: 2026年杭州师范大学程序设计基础课程多校联考第一场（补）
  Title: 矩形绘制
  https://pintia.cn/problem-sets/2115441217247838208/exam/problems/type/7?problemSetProblemId=2115441217461764099
*/
// @pintia code=start
#include <stdio.h>
void mprint(int, char);
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        if (i == 0 || i == n - 1) {
            mprint(m, '*');
        } else {
            if (m == 0)
                ;
            else if (m == 1) {
                mprint(1, '*');
            } else if (m >= 2) {
                mprint(1, '*');
                mprint(m - 2, ' ');
                mprint(1, '*');
            }
        }

        printf("\n");
    }

    return 0;
}
void mprint(int x, char c)
{
    for (int i = 0; i < x; i++) {
        printf("%c", c);
    }
}
// @pintia code=end