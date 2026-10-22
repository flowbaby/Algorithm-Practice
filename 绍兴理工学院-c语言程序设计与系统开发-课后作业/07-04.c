// 一个球从100m高度自由落下，每次落地后反跳回原高度的一半，再落下，再反弹。求它在第10次落地时，共经过多少米，第10次反弹多高。
#include <stdio.h>

int main()
{
    double height = 100;
    double move = 0;
    for (int i = 0; i < 10; i++) {
        move += height;
        if (i < 9) {
            move += height / 2;
        }
        height = height / 2;
    }
    printf("经过距离：%.4lf\n", move);
    printf("反弹高度：%.4lf\n", height);
    return 0;
}
