// 判断输入的英文字符串是否为回文。
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
    char text[MAX_LENGTH + 1];
    int left = 0;
    int right;
    int is_palindrome = 1;

    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 1;
    }
    remove_newline(text);

    right = 0;
    while (text[right] != '\0') {
        right++;
    }
    right--;

    while (left < right) {
        if (text[left] != text[right]) {
            is_palindrome = 0;
            break;
        }
        left++;
        right--;
    }

    if (is_palindrome) {
        printf("是回文\n");
    } else {
        printf("不是回文\n");
    }

    return 0;
}
