/*
 * 答案5-07 readlines使用主调数组
 *
 * 提示：把存储改成由 main 提供的字符数组 linestore，readlines 依次把
 * 每一行复制进该数组并让 lineptr[i] 指向其首字符，不再调用 alloc。
 * 这样避免了 alloc 的管理开销，通常比原版更快；实现时要注意检查
 * 行数上限与存储空间上限，超限返回 -1。
 */
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTOR 50000

char *lineptr[MAXLINES];
char linestore[MAXSTOR];

/* getline: 读入一行到 s，返回其长度 */
int getline(char *s, int lim)
{
    int c;
    char *t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - t;
}

/* readlines: 把输入行读入 lineptr，行存储在 linestore 中；返回行数，
 * 超限时返回 -1 */
int readlines(char *lineptr[], char *linestore, int maxlines)
{
    int len, nlines = 0;
    char line[MAXLEN];
    char *p = linestore;
    char *linestop = linestore + MAXSTOR;

    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p + len > linestop)
            return -1;
        else {
            line[len - 1] = '\0';   /* 去掉换行符 */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

/* writelines: 打印各行 */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int main(void)
{
    int nlines;

    if ((nlines = readlines(lineptr, linestore, MAXLINES)) >= 0) {
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("输入太大，无法排序\n");
        return 1;
    }
}
