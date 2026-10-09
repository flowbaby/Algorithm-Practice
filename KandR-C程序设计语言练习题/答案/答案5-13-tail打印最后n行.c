/*
 * 答案5-13 tail打印最后n行
 *
 * 提示：用指针数组 + 动态分配（malloc/realloc）存储各行，像 5.6 节排序
 * 程序那样，而不是固定大小的二维数组。n 可由 tail -n 指定，默认 10；
 * 输入行数不足 n 时打印全部，n 非法或过小时按合理方式处理（如 n<=0
 * 打印 0 行）。最后从第 (nlines-n) 行起打印即可。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000
#define DEFAULT_N 10

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

int main(int argc, char *argv[])
{
    int n = DEFAULT_N;
    char **lines = NULL;        /* 行指针数组（动态增长） */
    int nlines = 0, capacity = 0;
    char line[MAXLEN];
    int len, i, start;

    if (argc > 1 && argv[1][0] == '-')
        n = atoi(argv[1] + 1);
    if (n < 0)
        n = DEFAULT_N;

    while ((len = getline(line, MAXLEN)) > 0) {
        char *p;
        if (nlines >= capacity) {
            capacity = (capacity == 0) ? 100 : capacity * 2;
            lines = (char **)realloc(lines, capacity * sizeof(char *));
            if (lines == NULL) {
                printf("错误：存储不足\n");
                return 1;
            }
        }
        p = (char *)malloc(len);        /* len 已含 '\0' 的空间 */
        if (p == NULL) {
            printf("错误：存储不足\n");
            return 1;
        }
        line[len - 1] = '\0';           /* 去掉换行符 */
        strcpy(p, line);
        lines[nlines++] = p;
    }

    start = (nlines > n) ? nlines - n : 0;
    for (i = start; i < nlines; i++)
        printf("%s\n", lines[i]);
    return 0;
}
