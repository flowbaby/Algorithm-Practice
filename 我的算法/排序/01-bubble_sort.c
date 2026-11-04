#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int* arr, int n);
void bubble_sort1(int* arr, int n);
void bubble_sort2(int* arr, int n);

int main()
{
    int arr[100];
    srand((unsigned)time(NULL));
    generate_random_array(arr, 100);
    bubble_sort1(arr, 100);

    for (int i = 0; i < 100; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void generate_random_array(int* arr, int n)
{
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

void bubble_sort1(int* arr, int n)
{

    for (int end = n - 1; end > 0; end--) {
        int swapped = 0;
        for (int i = 0; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}
void bubble_sort2(int* arr, int n)
{
    // 进行几轮循环
    for (int i = 0; i < n - 1; i++) {
        // 每轮循环内元素比较
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}