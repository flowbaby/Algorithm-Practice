// 有 10 个数由大到小顺序存放在一个数组中，输入一个数，要求用折半查找法找出该数是数组中第几个元素的值。如果该数不在数组中，则输出 “无此数”。
#include <stdio.h>

int main(void)
{
    const int numbers[10] = { 100, 90, 80, 70, 60, 50, 40, 30, 20, 10 };
    int target;
    int left = 0;
    int right = 9;
    int position = -1;

    scanf("%d", &target);

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (numbers[middle] == target) {
            position = middle;
            break;
        }

        if (numbers[middle] > target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    if (position >= 0) {
        printf("该数是数组中的第 %d 个元素。\n", position + 1);
    } else {
        printf("无此数\n");
    }

    return 0;
}
