// 输入一行字符，分别统计出其中英文字母、空格、数字和其他字符的个数。
#include <stdio.h>

int main()
{
    int c;
    int i, j, k, l;
    i = j = k = l = 0;
    while ((c = getchar()) != EOF && c != '\n') {

        if (c >= '0' && c <= '9') {
            i++;
        } else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
            j++;
        } else if (c == ' ') {
            k++;
        } else {
            l++;
        }
    }
    printf("%d英文字母\n", j);
    printf("%d空格\n", k);
    printf("%d数字\n", i);
    printf("%d其他字符\n", l);

    return 0;
}
