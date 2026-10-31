// 有一个已排好序的数组，要求输入一个数后，按原来排序的规律将它插入数组中。如已有排序后的数组为：a[11]={11,22,33,44,55,66,77,88,99,100}
#include <stdio.h>
void insertion_sort(int* arr, int n);
int main()
{
    int a[11] = { 11, 22, 33, 44, 55, 66, 77, 88, 99, 100 };
    scanf("%d", &a[10]);
    insertion_sort(a, 11);
    for (int i = 0; i < 11; i++) {
        printf("%d\n", a[i]);
    }

    return 0;
}
void insertion_sort(int* arr, int n)
{
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}