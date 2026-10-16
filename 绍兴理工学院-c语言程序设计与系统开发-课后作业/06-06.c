// 输入两个正整数，求其最大公约数和最小公倍数。
#include <stdio.h>

int gcd(int, int);
int lcm(int, int);

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("gcd=%d,lcm=%d\n", gcd(a, b), lcm(a, b));
    return 0;
}

int gcd(int a, int b)
{
    int r = a % b;
    return r == 0 ? b : gcd(b, r);
}
int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}