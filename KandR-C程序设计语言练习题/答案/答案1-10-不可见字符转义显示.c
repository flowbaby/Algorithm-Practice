/*
 * 答案1-10 不可见字符转义显示
 *
 * 提示：在 getchar() 循环中分别判断三个特殊字符：制表符输出两个字符反斜杠和 t，退格符输出反斜杠和 b，反斜杠本身输出两个反斜杠。注意在字符串里写反斜杠要转义：printf("\\t") 实际打印 \t。
 */
#include <stdio.h>

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t')
            printf("\\t");
        else if (c == '\b')
            printf("\\b");
        else if (c == '\\')
            printf("\\\\");
        else
            putchar(c);
    }
    return 0;
}
