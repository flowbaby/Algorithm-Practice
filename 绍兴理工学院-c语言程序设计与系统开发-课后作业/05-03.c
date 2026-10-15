// 有一个分数序列：2/1,3/2,5/3,8/5,13/8,21/13,......
// 求出这个数列的前20项之和。
#include <stdio.h>

int main()
{
    int llast = 1;
    int last = 2;
    double sum = 0;
    for (int i = 0; i < 20; i++) {
        sum = sum + 1.0 * llast / last;
        int temp = last;
        last = llast + last;
        llast = temp;
    }
    printf("%d", sum);
    return 0;
}