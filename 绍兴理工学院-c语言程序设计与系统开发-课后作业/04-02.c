// 求s=1!+2!+3!+....10!的值。（！表示的是阶乘）
#include <stdio.h>

int fact(int);

int main()
{
    int s = 0;
    for (int i = 1; i <= 10; i++)
    {
        s += fact(i);
    }
    printf("s = %d", s);

    return 0;
}

int fact(int x){
    return x > 0 ? x*fact(x - 1) : 1;
}