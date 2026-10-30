// 求一个3*3的整型矩阵对角线元素之和。（矩阵值从键盘输入）
#include <stdio.h>

int main()
{
    int sum = 0;
    int arr[3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &arr[i][j]);
            if (i == j || 3 - 1 - i == j) {
                sum += arr[i][j];
            }
        }
    }
    printf("%d", sum);
    return 0;
}