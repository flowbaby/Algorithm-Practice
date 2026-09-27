/*
  @pintia psid=2102249416592003072 pid=2102249416612974593 compiler=GCC
  ProblemSet: 3.一维数组
  Title: 进制转换（2006慈溪）
  https://pintia.cn/problem-sets/2102249416592003072/exam/problems/type/7?problemSetProblemId=2102249416612974593
*/
// @pintia code=start
#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d", &n);
    getchar();
    int ch;
    const char d[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    int sum = 0;

    // 将任意进制数转换为10进制数sum
    while ((ch = getchar()) != '\n') {
        for (int i = 0; i < n; i++) {
            if (d[i] == ch) {
                ch = i;
                break;
            }
        }
        sum = sum * n + ch;
    }

    int m;
    scanf("%d", &m);
    // printf("sum=%d\n", sum);
    int x;
    char ret[31];
    if (sum == 0) {
        ret[0] = 0;
        ret[1] = '\0';
    } else {
        ret[0] = '\0';
        int len = strlen(ret);
        // printf("len=%d\n", len);
        // 输出要求进制数的值
        while (sum > 0) {
            x = sum % m;
            memmove(ret + 1, ret, len + 1);
            ret[0] = d[x];
            sum /= m;
            // printf("x=%c\n", d[x]);
            len++;
        }
    }
    printf("%s", ret);
    return 0;
}

// @pintia code=end