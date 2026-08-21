#include <stdio.h>

int main()
{
    int c;
    int num1, num2, num3;

    num1 = num2 = num3 = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            num1++;
        } else if (c == '\t') {
            num2++;
        } else if (c == '\n') {
            num3++;
        }
    }
    printf("空格数量：%d,制表符数量：%d,换行符数量：%d", num1, num2, num3);
    return 0;
}