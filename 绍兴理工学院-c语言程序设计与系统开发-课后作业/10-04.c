// 输入一个以回车符为结束标志的字符串（少于 10 个字符），提取其中的所有数字字符, 将其转换为一个十进制整数, 再将十进制整数转化为二进制数输出。
#include <ctype.h>
#include <stdio.h>

#define MAX_LENGTH 10

void print_binary(unsigned int number)
{
    char digits[sizeof(unsigned int) * 8];
    int count = 0;

    if (number == 0) {
        printf("0\n");
        return;
    }

    while (number > 0) {
        digits[count] = (char)('0' + number % 2);
        number /= 2;
        count++;
    }

    for (int i = count - 1; i >= 0; i--) {
        putchar(digits[i]);
    }
    putchar('\n');
}

int main(void)
{
    char text[MAX_LENGTH + 1];
    unsigned int decimal = 0;

    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 1;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        if (isdigit((unsigned char)text[i])) {
            decimal = decimal * 10 + (unsigned int)(text[i] - '0');
        }
    }

    print_binary(decimal);
    return 0;
}
