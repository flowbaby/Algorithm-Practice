// 时间限制
// 400 ms
// 内存限制
// 65536 kB
// 代码长度限制
// 8000 B
// 判题程序
// Standard
// 作者
// 张彤彧（浙江大学）
// 输入一个以#结束的字符串，本题要求将小写字母全部转换成大写字母，把大写字母全部转换成小写字母，其它字符不变。

// 输入格式：

// 输入在一行中给出一个长度不超过40的、以#结束的非空字符串。

// 输出格式：

// 在一行中按照要求输出转换后的字符串。

// 输入样例：
// Hello World! 123#
// 输出样例：
// hELLO wORLD! 123

#include <stdio.h>

int main()
{
    char c;
    scanf("%c", &c);
    while (c != '#') {
        if (c > 'a' && c < 'z') {
            printf("%c", c + 'A' - 'a');
        } else if (c > 'A' && c < 'Z') {
            printf("%c", c - 'A' + 'a');
        } else {
            printf("%c", c);
        }
        scanf("%c", &c);
    }

    return 0;
}