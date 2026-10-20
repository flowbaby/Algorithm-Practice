/*
  @pintia psid=2112024321886732288 pid=2112024322071298054 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: 吃黄焖鸡吗
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298054
*/
// @pintia code=start
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int* a = (int*)malloc(m * sizeof(int));
    int min[2] = { 1e4, 1e4 };
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
        if (a[i] < min[0]) {
            min[1] = min[0];
            min[0] = a[i];
        } else if (a[i] < min[1]) {
            min[1] = a[i];
        }
    }
    if (n - m >= 2) {
        printf("%d", 20);
    } else if (n - m == 1) {
        printf("%d", min[0] + 20);
    } else {
        printf("%d", min[1] + 20);
    }

    free(a);
    return 0;
}
// @pintia code=end