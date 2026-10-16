// 输出以下图形

//             *  1个*，0个空格，前面6个空格
//           * * *  3个*，2个空格，前面4个空格
//         * * * * *  5个*，4个空格，前面2个空格
//       * * * * * * *  7个*，6个空格，前面0个空格
//         * * * * *
//           * * *
//             *
// 前面空格数+*的数量保存不变
#include <stdio.h>

void print_stars(int row, int total_row);

int main()
{
    int total_row = 7;
    for (int i = 1; i <= total_row / 2 + 1; i++) {
        print_stars(i, total_row);
    }
    for (int i = total_row / 2; i > 0; i--) {
        print_stars(i, total_row);
    }

    return 0;
}

void print_stars(int row, int total_row)
{
    int star_num = row + row - 1;
    for (int j = 0; j < total_row - star_num; j++) {
        printf(" ");
    }
    for (int j = 0; j < star_num; j++) {
        printf("*");
        if (!(j == star_num - 1))
            printf(" ");
    }
    printf("\n");
}
