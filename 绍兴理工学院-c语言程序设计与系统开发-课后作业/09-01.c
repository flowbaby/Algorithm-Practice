// 杨辉三角形（输出两种图形）
#include <stdio.h>

#define ROWS 10

void build_pascal_triangle(int triangle[ROWS][ROWS])
{
    for (int i = 0; i < ROWS; i++) {
        triangle[i][0] = 1;
        triangle[i][i] = 1;

        for (int j = 1; j < i; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
}

void print_left_aligned(const int triangle[ROWS][ROWS])
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j <= i; j++) {
            if (j > 0) {
                printf(" ");
            }
            printf("%d", triangle[i][j]);
        }
        printf("\n");
    }
}

void print_centered(const int triangle[ROWS][ROWS])
{
    for (int i = 0; i < ROWS; i++) {
        for (int space = 0; space < ROWS - i - 1; space++) {
            printf("  ");
        }

        for (int j = 0; j <= i; j++) {
            printf("%4d", triangle[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
    int triangle[ROWS][ROWS] = { 0 };

    build_pascal_triangle(triangle);
    print_left_aligned(triangle);
    printf("\n");
    print_centered(triangle);

    return 0;
}
