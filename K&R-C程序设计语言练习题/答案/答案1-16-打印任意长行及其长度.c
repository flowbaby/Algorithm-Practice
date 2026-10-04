/*
 * 答案1-16 打印任意长行及其长度
 *
 * 提示：关键在于 getline：即使一行超过缓冲区长度 lim-1，也要继续把该行读完并返回真实长度，只在缓冲区放得下的范围内保存字符（超出部分丢弃）。主函数据此打印完整长度和尽可能多的文本。
 */
#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line; correctly handle arbitrarily long lines */
int main()
{
    int len;                /* current line length */
    int max;                /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) {  /* there was a line */
        printf("Length: %d\n", max);
        printf("%s", longest);
        printf("\n");
    }
    return 0;
}

/* getline: read a line into s, return its full length;
   if the line is longer than lim, count the rest but do not store it */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (i < lim - 1)
            s[i] = c;
        ++i;
    }
    if (c == '\n') {
        if (i < lim - 1)
            s[i] = c;
        ++i;
    }
    if (i < lim)
        s[i] = '\0';
    else
        s[lim - 1] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
