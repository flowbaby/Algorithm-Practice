// 求s=k+k^2+1/k(第一个K范围为1-100，第二个范围1-50，第三个范围1-10)

#include <stdio.h>

int main()
{
    double s = 0;
    for (int i = 1; i <= 100; i++) {
        s += i;
    }
    for (int i = 1; i <= 50; i++) {
        s += i * i;
    }
    for (int i = 1; i <= 10; i++) {
        s += 1.0 / i;
    }
    printf("%f", s);
    return 0;
}