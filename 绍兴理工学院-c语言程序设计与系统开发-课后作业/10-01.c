// 编一个程序，将两个字符串连接起来，不要用 strcat 函数。（课堂完成）
#include <stdio.h>

#define MAX_LENGTH 100

void remove_newline(char text[])
{
    int i = 0;

    while (text[i] != '\0') {
        if (text[i] == '\n' || text[i] == '\r') {
            text[i] = '\0';
            return;
        }
        i++;
    }
}

int main(void)
{
    char first[MAX_LENGTH * 2 + 1];
    char second[MAX_LENGTH + 1];
    int length = 0;
    int i = 0;

    if (fgets(first, sizeof(first), stdin) == NULL
        || fgets(second, sizeof(second), stdin) == NULL) {
        return 1;
    }

    remove_newline(first);
    remove_newline(second);

    while (first[length] != '\0') {
        length++;
    }

    while (second[i] != '\0') {
        first[length] = second[i];
        length++;
        i++;
    }
    first[length] = '\0';

    printf("%s\n", first);
    return 0;
}
