#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int* arr, int n);

int main()
{
    int arr[1000];
    srand((unsigned)time(NULL));
    generate_random_array(arr, 1000);

    // code

    for (int i = 0; i < 1000; i++) {
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