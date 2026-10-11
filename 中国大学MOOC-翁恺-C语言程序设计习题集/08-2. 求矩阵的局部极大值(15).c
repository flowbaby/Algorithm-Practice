// 时间限制
// 400 ms
// 内存限制
// 65536 kB
// 代码长度限制
// 8000 B
// 判题程序
// Standard
// 作者
// 徐镜春（浙江大学）
// 给定M行N列的整数矩阵A，如果A的非边界元素A[i][j]大于相邻的上下左右4个元素，那么就称元素A[i][j]是矩阵的局部极大值。本题要求给定矩阵的全部局部极大值及其所在的位置。

// 输入格式：

// 输入在第1行中给出矩阵A的行数M和列数N（3<=M,N<=20）；最后M行，每行给出A在该行的N个元素的值。数字间以空格分隔。

// 输出格式：

// 每行按照“元素值 行号 列号”的格式输出一个局部极大值，其中行、列编号从1开始。要求按照行号递增输出；若同行有超过1个局部极大值，则该行按列号递增输出。若没有局部极大值，则输出“None 总行数 总列数”。

// 输入样例1：
// 4 5
// 1 1 1 1 1
// 1 3 9 3 1
// 1 5 3 5 1
// 1 1 1 1 1
// 输出样例1：
// 9 2 3
// 5 3 2
// 5 3 4
// 输入样例2：
// 3 5
// 1 1 1 1 1
// 9 3 9 9 1
// 1 5 3 5 1
// 输出样例2：
// None 3 5
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int M, N;
    scanf("%d %d", &M, &N);
    int** arr = (int**)malloc(M * sizeof(int*));
    // 分配列空间
    for (int i = 0; i < M; i++) {
        arr[i] = (int*)malloc(N * sizeof(int));
    }
    // 填充数据
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    // 找出局部最大值
    int falg = 0;
    for (int i = 1; i < M - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            if (arr[i][j] > arr[i - 1][j] && arr[i][j] > arr[i + 1][j] && arr[i][j] > arr[i][j - 1] && arr[i][j] > arr[i][j + 1]) {
                printf("%d %d %d\n", arr[i][j], i + 1, j + 1);
                falg = 1;
            }
        }
    }
    if (!falg) {
        printf("None %d %d", M, N);
    }

    free(arr);
    arr = NULL;
    return 0;
}