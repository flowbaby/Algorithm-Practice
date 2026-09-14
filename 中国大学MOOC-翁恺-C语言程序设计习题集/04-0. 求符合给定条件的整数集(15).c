// 时间限制
// 400 ms
// 内存限制
// 65536 kB
// 代码长度限制
// 8000 B
// 判题程序
// Standard
// 作者
// 徐镜春（浙江大学）
// 给定不超过6的正整数A，考虑从A开始的连续4个数字。请输出所有由它们组成的无重复数字的3位数。

// 输入格式：

// 输入在一行中给出A。

// 输出格式：

// 输出满足条件的的3位数，要求从小到大，每行6个整数。整数间以空格分隔，但行末不能有多余空格。

// 输入样例：
// 2
// 输出样例：
// 234 235 243 245 253 254
// 324 325 342 345 352 354
// 423 425 432 435 452 453
// 523 524 532 534 542 543
#include <stdio.h>

int main()
{
    int input;
    int lower, upper;
    int cur1, cur2, cur3;
    int count = 0;

    scanf("%d", &input);
    cur3 = cur2 = cur1 = lower = input;
    upper = input + 3;

    for (int i = 0; i < 4; i++) {
        cur3 = lower;
        cur2 = lower;
        count = 0;
        for (int j = 0; j < 6; j++) {
            printf("%d", cur1);
            if (count == 2) {
                count = 0;
                cur2++;
                if (cur2 > upper) {
                    cur2 = lower;
                }
            }
            if (cur2 == cur1) {
                cur2++;
                if (cur2 > upper) {
                    cur2 = lower;
                }
            }
            count++;
            printf("%d", cur2);

            while (cur3 == cur1 || cur3 == cur2) {
                cur3++;
                if (cur3 > upper) {
                    cur3 = lower;
                }
            }
            printf("%d ", cur3);
            cur3++;
            if (cur3 > upper) {
                cur3 = lower;
            }
        }
        cur1++;
        printf("\n");
    }
}