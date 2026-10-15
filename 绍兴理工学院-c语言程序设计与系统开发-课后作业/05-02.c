// 一个数如果恰好等于它的因子之和，这个数就称为“完数”。例如：6的因子1，2，3，而6=1+2+3，因为6是完数。编程找出1000以内的所有完数，并按下面格式输出：6 its factors are 1,2,3
#include <stdio.h>
int main()
{
    for (int num = 1; num <= 1000; num++) {
        int sum = 0;

        for (int j = 1; j <= num / 2; j++) {
            if (num % j == 0)
                sum += j;
        }
        if (sum == num) {
            printf("%d its factors are ", num);

            int first = 1;

            for (int j = 1; j <= num / 2; j++) {
                if (num % j == 0) {
                    printf(first ? "%d" : ",%d", j);
                    first = 0;
                }
            }
            printf("\n");
        }
    }
    return 0;
}
