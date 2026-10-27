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
// 输入一个字符串，对该字符串进行逆序，输出逆序后的字符串。

// 输入格式：

// 输入在一行中给出一个不超过80个字符长度的、以回车结束的非空字符串。

// 输出格式：

// 在一行中输出逆序后的字符串。

// 输入样例：
// Hello World!
// 输出样例：
// !dlroW olleH
#include <stdio.h>
#include <string.h>
int main()
{
    char str[40][81];
    char new[40][81];
    int i = 0;
    while (scanf("%s", str[i]) == 1) {
        i++;
    }
    i--;
    // 按照空格分隔原数组，并反转
    int len = i;
    for (int j = 0; j <= len; j++) {
        strcpy(new[j], str[i]);
        i--;
    }
    // 将每个字符串内部反转
    for (int j = 0; j <= len; j++) {
        char nstr[81]={0};
        int newlen = strlen(new[j]);
        for (int k = 0; k < strlen(new[j]); k++) {
            nstr[k] = new[j][newlen-1];
            newlen--;
        }
        printf("%s", nstr);
        if (j < len) {
            printf(" ");
        }
    }

    return 0;
}