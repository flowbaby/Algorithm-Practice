/*
 * 答案1-17 打印超过80字符的行
 *
 * 提示：用 getline 逐行读入，若该行长度（含或不含换行符）大于 80 则整行打印。把 80 定义为符号常量 MINLEN，便于修改阈值。
 */
#include <stdio.h>

#define MAXLINE 1000
#define MINLEN 80       /* minimum length to print */

int getline(char line[], int maxline);

/* print all input lines longer than 80 characters */
int main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > MINLEN)
            printf("%s", line);
    }
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
