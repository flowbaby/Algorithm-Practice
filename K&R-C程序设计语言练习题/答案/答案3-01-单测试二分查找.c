/*
 * 答案3-01 单测试二分查找
 *
 * 提示：把循环体内的两次测试合并为一次——循环条件只判断“还没找到”（x != v[mid]），
 * 配合 low <= high 的收缩；找到后退出循环，在循环外再补一次相等性测试。
 * 注意 mid 的更新与 low/high 的收缩要一致，避免死循环；边界情况（找不到、单元素数组）
 * 都要能正确返回 -1 或正确下标。
 */
#include <stdio.h>

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low + high) / 2;
    while (low < high && x != v[mid]) {
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
        mid = (low + high) / 2;
    }
    if (x == v[mid])
        return mid;
    else
        return -1;
}

int main(void)
{
    int v[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int i, x;

    for (i = 0; i < 10; i++)
        printf("%d ", v[i]);
    printf("\n");

    x = 7;
    printf("binsearch(%d) = %d\n", x, binsearch(x, v, 10));
    x = 8;
    printf("binsearch(%d) = %d\n", x, binsearch(x, v, 10));
    x = 1;
    printf("binsearch(%d) = %d\n", x, binsearch(x, v, 10));
    x = 19;
    printf("binsearch(%d) = %d\n", x, binsearch(x, v, 10));

    return 0;
}
