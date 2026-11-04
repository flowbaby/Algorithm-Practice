// 时间限制
// 400 ms
// 内存限制
// 65536 kB
// 代码长度限制
// 8000 B
// 判题程序
// Standard
// 作者
// 白洪欢（浙江大学）
// 输入一个字符串和一个非负整数N，要求将字符串循环左移N次。

// 输入格式：

// 输入在第1行中给出一个不超过100个字符长度的、以回车结束的非空字符串；第2行给出非负整数N。

// 输出格式：

// 在一行中输出循环左移N次后的字符串。

// 输入样例：
// Hello World!
// 2
// 输出样例：
// llo World!He
#include <stdio.h>
#include <string.h>
int main()
{
    char str[101];
    gets(str);
    int n;
    scanf("%d", &n);
    int len = strlen(str);
    n = n % len;
    char* arr = malloc(n * sizeof(char));
    for (int i = 0; i < n; i++) {
        arr[i] = str[i];
    }
    for (int i = 0; i < len - n; i++) {
        str[i] = str[i + n];
    }
    int j = 0;
    for (int i = len - n; i < len; i++) {
        str[i] = arr[j++];
    }

    free(arr);
    printf("%s", str);
    return 0;
}