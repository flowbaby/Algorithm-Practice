// 输出100以内的素数，要求每行5个。
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n=100;
    // scanf("%d", &n);
    int* is_prime = (int*)calloc(n + 1, sizeof(int));
    int* primes = (int*)malloc((n + 1) * sizeof(int));
    int count = 0;

    for (int i = 2; i <= n; i++) {
        if (!is_prime[i]) {
            primes[count++] = i;
        }

        for (int j = 0; j < count && i * primes[j] <= n; j++) {
            is_prime[i * primes[j]] = 1;
            if (i % primes[j]==0)
                break;
        }
    }
    primes = (int*)realloc(primes, count * sizeof(int));
    for (int i = 0; i < count; i++) {
        printf("%d", primes[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        } else if (!(i == count - 1)) {
            printf(" ");
        }
    }

    free(is_prime);
    free(primes);
    return 0;
}