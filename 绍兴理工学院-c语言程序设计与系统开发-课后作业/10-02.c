// 编写一个程序，将字符数组 S2 中的全部字符复制到字符数组 S1 中。不用 strcpy 函数。复制时，‘\0’也要复制过去。‘\0’后面的字符不复制。（课堂完成）
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
    char source[MAX_LENGTH + 1];
    char destination[MAX_LENGTH + 1];
    int i = 0;

    if (fgets(source, sizeof(source), stdin) == NULL) {
        return 1;
    }
    remove_newline(source);

    do {
        destination[i] = source[i];
        i++;
    } while (source[i - 1] != '\0');

    printf("%s\n", destination);
    return 0;
}
