/*
 * 答案1-19 字符串反转reverse
 *
 * 提示：reverse 用两个下标 i、j 从两端向中间逐个交换字符。注意跳过行尾的 '\n'，让它留在字符串末尾，保证反转后换行符仍在行尾。getline 读入一行，reverse 后原样输出。
 */
#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void reverse(char s[]);

/* reverse each input line a line at a time */
int main()
{
    char line[MAXLINE];

    while (getline(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
    }
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* reverse: reverse the character string s in place */
void reverse(char s[])
{
    int i, j;
    char temp;

    j = 0;
    while (s[j] != '\0')
        ++j;
    --j;                    /* skip the terminating '\0' */
    if (s[j] == '\n')
        --j;                /* leave the newline at the end */

    for (i = 0; i < j; ++i, --j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}
