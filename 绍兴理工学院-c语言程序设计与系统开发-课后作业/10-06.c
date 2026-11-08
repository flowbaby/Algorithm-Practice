// 输入一行字符，统计其中有多少个单词，单词之间用空格分隔开。
#include <ctype.h>
#include <stdio.h>

#define MAX_LENGTH 200

int main(void)
{
    char text[MAX_LENGTH + 1];
    int in_word = 0;
    int word_count = 0;

    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 1;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char current = (unsigned char)text[i];

        if (isspace(current)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            word_count++;
        }
    }

    printf("%d\n", word_count);
    return 0;
}
