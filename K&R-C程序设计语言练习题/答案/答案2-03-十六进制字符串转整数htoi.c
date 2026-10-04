/*
 * 答案2-03 十六进制字符串转整数htoi
 *
 * 提示：先跳过可选的 0x/0X 前缀，然后对每个十六进制数字按
 * result = result * 16 + digit 累加。数字 0~9、a~f、A~F 分别转换为
 * 0~15，遇到非法字符即停止转换。
 */
#include <stdio.h>

int htoi(char s[])
{
    int i, n, d;

    n = 0;
    i = 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        i = 2;
    for (; s[i] != '\0'; ++i) {
        if (s[i] >= '0' && s[i] <= '9')
            d = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            d = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            d = s[i] - 'A' + 10;
        else
            break;
        n = n * 16 + d;
    }
    return n;
}

int main(void)
{
    printf("%s -> %d\n", "0xFF", htoi("0xFF"));
    printf("%s -> %d\n", "0X1a", htoi("0X1a"));
    printf("%s -> %d\n", "10", htoi("10"));
    printf("%s -> %d\n", "dead", htoi("dead"));
    return 0;
}
