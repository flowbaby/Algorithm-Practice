// 打印Fabonacci数列的前40项（每行出4项）

// 数列规则如下：1，2，3，5，8，……
#include <stdio.h>

int main()
{
    int llast = 0;
    int last = 1;
    int new;
    for (int i = 1; i <= 40; i++) {
        new = llast + last;
        llast = last;
        last = new;
        printf("%d", new);
        if (i % 4 == 0) {
            printf("\n");
        } else {
            printf(" ");
        }
    }

    return 0;
}