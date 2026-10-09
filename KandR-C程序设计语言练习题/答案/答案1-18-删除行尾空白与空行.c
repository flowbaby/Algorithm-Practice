/*
 * 答案1-18 删除行尾空白与空行
 *
 * 提示：先读整行，再从行尾（换行符之前）向前扫描，把末尾的空格和制表符去掉，重新写回换行符与字符串结束符。若去掉后该行已无任何内容，则整行删除不输出。
 */
#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int removetrail(char s[]);

/* remove trailing blanks and tabs, and delete entirely blank lines */
int main()
{
    char line[MAXLINE];

    while (getline(line, MAXLINE) > 0)
        if (removetrail(line) > 0)
            printf("%s", line);
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

/* removetrail: remove trailing blanks and tabs from s; return new length */
int removetrail(char s[])
{
    int i;

    i = 0;
    while (s[i] != '\n' && s[i] != '\0')
        ++i;
    --i;                        /* back off from '\n' or end of string */
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
        --i;
    if (i >= 0) {               /* a non-blank character remains */
        ++i;
        s[i] = '\n';
        ++i;
        s[i] = '\0';
    }
    return i;
}
