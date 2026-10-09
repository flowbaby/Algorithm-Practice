// 时间限制
// 100 ms
// 内存限制
// 65536 kB
// 代码长度限制
// 8000 B
// 判题程序
// Standard
// 作者
// CHEN, Yue
// 令P_i表示第i个素数。现任给两个正整数M <= N <= 10^4，请输出P_M到P_N的所有素数。

// 输入格式：

// 输入在一行中给出M和N，其间以空格分隔。

// 输出格式：

// 输出从P_M到P_N的所有素数，每10个数字占1行，其间以空格分隔，但行末不得有多余空格。

// 输入样例：
// 5 27
// 输出样例：
// 11 13 17 19 23 29 31 37 41 43
// 47 53 59 61 67 71 73 79 83 89
// 97 101 103
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 105000

/**
 * @brief 埃氏素数筛
 *
 * @param max 可能存在的最大的素
 * @return int* 返回一个数组
 */
int* prime1(int max);

int* prime2(int max);

int main()
{
    int M, N;
    scanf("%d %d", &M, &N);
    int* isPrime = prime2(MAX);

    int count = 0;
    int num = 0;
    for (int i = 2; i <= MAX; i++) {
        if (!isPrime[i]) {
            count++;
            if (count >= M && count <= N) {
                printf("%d", i);
                num++;
                if (num % 10 == 0) {
                    printf("\n");
                } else {
                    printf(" ");
                }
            } else if (count > N) {
                break;
            }
        }
    }

    free(isPrime);
    isPrime = NULL;
    return 0;
}

int* prime1(int max)
{
    int* isPrime = (int*)malloc((max + 1) * sizeof(int));
    memset(isPrime, 0, (max + 1) * sizeof(int));

    for (int i = 2; i * i <= max; i++) {
        if (!isPrime[i]) {
            for (int j = i * i; j <= max; j += i) {
                isPrime[j] = 1;
            }
        }
    }

    return isPrime;
}

int* prime2(int max)
{
    int* isPrime = (int*)malloc((max + 1) * sizeof(int));
    memset(isPrime, 0, (max + 1) * sizeof(int));
    int* prime = (int*)malloc((max + 1) * sizeof(int));
    memset(prime, 0, (max + 1) * sizeof(int));

    int primeNum = 0;

    for (int i = 2; i <= max; i++) {
        if (!isPrime[i]) {
            prime[primeNum] = i;
            primeNum++;
        }
        for (int j = 0; j < primeNum && i * prime[j] <= max; j++) {
            isPrime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }

    free(prime);
    prime = NULL;
    return isPrime;
}