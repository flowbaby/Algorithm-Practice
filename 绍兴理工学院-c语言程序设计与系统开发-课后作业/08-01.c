// 用选择法对10个整数排序（冒泡法和选择法）。
#include <stdio.h>

void selection_sort(int* arr, int n);

int main()
{
    int arr[10] = { 293, 5645, 574, 89234, 2, 465634, 999, 3, 54, 11 };
    selection_sort(arr, sizeof(arr) / sizeof(int));
    for (int i = 0; i < 10; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}

void selection_sort(int* arr, int n)
{
    if (n < 2) {
        return;
    }
    // 外层循环 i 用来区分排序部分和未排序部分
    // i 前面元素为已排序部分
    // i 后面元素为未排序部分
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;

        // 内层循环 j 用来扫描数组找出最小的数
        for (int j = i + 1; j < n; j++) {
            if (arr[min_index] > arr[j]) {
                min_index = j;
            }
        }

        // 交换下一个要被排序的索引上的元素和最小的元素的位置
        if (min_index != i) {
            int temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
        }
    }
}