/*
  @pintia psid=2112024660870381568 pid=2112024661063319562 compiler=GCC
  ProblemSet: 2022学年秋学期程序设计基础联考第一场
  Title: 初等元素反应论
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319562
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        char ch1, ch2;
        int d1, d2;
        scanf(" %c %c %d %d", &ch1, &ch2, &d1, &d2);
        int sum;

        // 元素类型相同
        if (ch1 == ch2 || ch1 + 'A' - 'a' == ch2 || ch1 == ch2 + 'A' - 'a') {
            sum = d1 + d2;
            printf("%d\n", sum);
            if (ch1 >= 'A' && ch1 <= 'D') {
                printf("%c\n", ch1);
            } else if (ch2 >= 'A' && ch2 <= 'D') {
                printf("%c\n", ch2);
            } else if (ch1 >= 'a' && ch1 <= 'd') {
                printf("%c\n", ch1); // 两个弱元素，附着弱元素
            }
        }
        // 弱弱
        else if (ch1 >= 'a' && ch1 <= 'd' && ch2 >= 'a' && ch2 <= 'd') {
            sum = d1 + d2 + d1 * d2;
            printf("%d\n", sum);
        }
        // 强弱
        else if (ch1 >= 'A' && ch1 <= 'D' && ch2 >= 'a' && ch2 <= 'd' || ch1 >= 'a' && ch1 <= 'd' && ch2 >= 'A' && ch2 <= 'D') {
            sum = d1 + d2 + 2 * d1 * d2;
            printf("%d\n", sum);
            if (ch1 >= 'A' && ch1 <= 'D') {
                printf("%c\n", ch1);
            } else if (ch2 >= 'A' && ch2 <= 'D') {
                printf("%c\n", ch2);
            }
        }
        // 强强
        else if (ch1 >= 'A' && ch1 <= 'D' && ch2 >= 'A' && ch2 <= 'D') {
            sum = d1 + d2 + 3 * d1 * d2;
            printf("%d\n", sum);
            printf("%c %c\n", ch1 + 'a' - 'A', ch2 + 'a' - 'A');
        }
        // 弱扩散
        else if (ch1 >= 'a' && ch1 <= 'd' && ch2 == 'E') {
            sum = (d1 + d2) * 2;
            printf("%d\n", sum);

        }
        // 强元素扩散
        else if (ch1 >= 'A' && ch1 <= 'D' && ch2 == 'E') {
            sum = (d1 * 2 + d2) * 2;
            printf("%d\n", sum);
            printf("%c\n", ch1);
        }
    }

    return 0;
}
// @pintia code=end