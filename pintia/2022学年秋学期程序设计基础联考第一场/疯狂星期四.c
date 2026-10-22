/*
  @pintia psid=2112024660870381568 pid=2112024661063319555 compiler=GCC
  ProblemSet: 2022-2023 学年秋学期程序设计基础联考第一场
  Title: 疯狂星期四
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319555
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    long long x, y, z;
    scanf("%lld %lld %lld", &x, &y, &z);
    long long a, b, c, d;
    scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
    long long k;
    scanf("%lld", &k);

    // 找出最小的代金券
    long long min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    if (d < min) {
        min = d;
    }

    // 能支付最高的价格
    long long money = (a + b + c + d - min) * k;

    // 找出能支付的最贵的套餐
    long long max = -1;

    if (x > max && money >= x) {
        max = x;
    }

    if (y > max && money >= y) {
        max = y;
    }
    if (z > max && money >= z) {
        max = z;
    }

    // 打印结果
    if (max == -1) {
        printf("POOR");
    } else {
        if (max == x) {
            printf("A");
        } else if (max == y) {
            printf("B");
        } else if (max == z) {
            printf("C");
        }
    }
    printf("\n");
    return 0;
}
// @pintia code=end