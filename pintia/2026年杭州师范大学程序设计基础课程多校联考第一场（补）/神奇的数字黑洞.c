/*
  @pintia psid=2115441217247838208 pid=2115441217461764105 compiler=GCC
  ProblemSet: 2026年杭州师范大学程序设计基础课程多校联考第一场（补）
  Title: 神奇的数字黑洞
  https://pintia.cn/problem-sets/2115441217247838208/exam/problems/type/7?problemSetProblemId=2115441217461764105
*/
// @pintia code=start
#include <stdio.h>

static int kaprekar_next(int n)
{
    int d[4];

    /* 固定提取四位，自动完成高位补 0 */
    for (int i = 3; i >= 0; --i) {
        d[i] = n % 10;
        n /= 10;
    }

    /* 四位数字升序排序 */
    for (int i = 1; i < 4; ++i) {
        int key = d[i];
        int j = i - 1;

        while (j >= 0 && d[j] > key) {
            d[j + 1] = d[j];
            --j;
        }
        d[j + 1] = key;
    }

    int small = 0;
    int large = 0;

    for (int i = 0; i < 4; ++i) {
        small = small * 10 + d[i]; /* 升序构成最小数 */
        large = large * 10 + d[3 - i]; /* 降序构成最大数 */
    }

    return large - small;
}

int main(void)
{
    int T;

    if (scanf("%d", &T) != 1) {
        return 0;
    }

    while (T--) {
        int n;
        int step = 0;

        scanf("%d", &n);

        /*
         * 6174 是固定点。
         * 四位数如果四次重排后为 0，说明数字全都相同，
         * 会永远停留在 0，无法到达 6174。
         */
        while (n != 6174 && n != 0) {
            n = kaprekar_next(n);
            ++step;
        }

        if (n == 6174) {
            printf("%d\n", step);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}
// @pintia code=end