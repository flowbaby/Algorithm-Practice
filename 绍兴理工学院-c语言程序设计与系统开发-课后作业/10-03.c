// 输入 3 个字符串，要求找出其中最大的。（课堂完成）
#include <stdio.h>
#include <string.h>

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
    char first[MAX_LENGTH + 1];
    char second[MAX_LENGTH + 1];
    char third[MAX_LENGTH + 1];

    if (fgets(first, sizeof(first), stdin) == NULL
        || fgets(second, sizeof(second), stdin) == NULL
        || fgets(third, sizeof(third), stdin) == NULL) {
        return 1;
    }

    remove_newline(first);
    remove_newline(second);
    remove_newline(third);

    const char* largest = first;
    if (strcmp(second, largest) > 0) {
        largest = second;
    }
    if (strcmp(third, largest) > 0) {
        largest = third;
    }

    printf("%s\n", largest);
    return 0;
}
