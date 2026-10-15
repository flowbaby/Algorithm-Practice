// 求s=a+aa+aaa+aaaa+.....的值，其中a是一个数字,n表示a的位数，例如：2+22+222+2222+22222（此时a=2,n=5）,a,n由键盘输入。
#include <stdio.h>

int main()
{
    int a, n;
    scanf("%d %d", &a, &n);
    int sum = 0;
    int S = 0;
    for (int i = 0; i < n; i++) {
        sum = sum * 10 + a;
        S = S + sum;
    }
    printf("%d\n", S);
    return 0;
}