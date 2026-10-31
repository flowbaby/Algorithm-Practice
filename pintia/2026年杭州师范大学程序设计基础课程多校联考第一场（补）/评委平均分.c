/*
  @pintia psid=2115441217247838208 pid=2115441217461764100 compiler=GCC
  ProblemSet: 2026年杭州师范大学程序设计基础课程多校联考第一场（补）
  Title: 评委平均分
  https://pintia.cn/problem-sets/2115441217247838208/exam/problems/type/7?problemSetProblemId=2115441217461764100
*/
// @pintia code=start
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int N;
    int min = 100, max = 0;
    scanf("%d", &N);
    int* arr = (int*)malloc(N * sizeof(int));
    int sum = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
        sum += arr[i];
    }
    sum = sum - max - min;
    double ave = 1.0 * sum / (N - 2);
    printf("%.2lf", ave);
    free(arr);
    return 0;
}
// @pintia code=end