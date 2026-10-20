/*
  @pintia psid=2112024321886732288 pid=2112024322071298055 compiler=GCC
  ProblemSet: 2023学年秋学期程序设计基础联考第一场
  Title: 小瑾的A与C
  https://pintia.cn/problem-sets/2112024321886732288/exam/problems/type/7?problemSetProblemId=2112024322071298055
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        int n;
        scanf("%d", &n);
        int cnt = 0;
        int one = 1;
        for (int j = 0; j < n; j++) {
            char ch;
            scanf(" %c", &ch);
            if (ch == 'C') {
                cnt++;
            } else {
                if (one == 1) {
                    one = 0;
                } else {
                    printf(" ");
                }
                printf("%c", ch);
            }
        }
        for (int j = 0; j < cnt; j++) {
            if (one == 1) {
                one = 0;
            } else {
                printf(" ");
            }
            printf("A");
        }
        printf("\n");
    }

    return 0;
}
// @pintia code=end