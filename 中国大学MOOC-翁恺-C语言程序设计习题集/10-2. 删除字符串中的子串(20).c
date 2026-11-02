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
// 输入2个字符串S1和S2，要求删除字符串S1中出现的所有子串S2，即结果字符串中不能包含S2。

// 输入格式：

// 输入在2行中分别给出不超过80个字符长度的、以回车结束的2个非空字符串，对应S1和S2。

// 输出格式：

// 在一行中输出删除字符串S1中出现的所有子串S2后的结果字符串。

// 输入样例：
// Tomcat is a male ccatat
// cat
// 输出样例：
// Tom is a male
#include <stdio.h>
#include <string.h>
int main()
{
    char str1[81];
    char str2[81];
    gets(str1);
    gets(str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int swap = 0;
    do {
        swap = 0;
        for (int i = 0; i < len1; i++) {
            int flag = 1;
            int index = i;
            for (int j = 0; j < len2; j++) {
                if (str1[index] == str2[j]) {
                    index++;
                } else {
                    flag = 0;
                    break;
                }
            }
            // 删除从i到index（包含）的元素
            // index 后面的元素全向前移动strlen(str2)格
            if (flag) {
                swap = 1;
                for (int k = i; k < len1 - len2 + 1; k++) {
                    str1[k] = str1[k + len2];
                }
            }
        }
    } while (swap);
    printf("%s", str1);
    return 0;
}