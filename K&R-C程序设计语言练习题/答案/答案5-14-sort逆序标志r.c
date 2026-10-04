/*
 * 答案5-14 sort逆序标志r
 *
 * 提示：在 5.6 节排序程序的基础上增加 -r 标志。qsort 增加一个 reverse
 * 参数，比较结果在交换时取反即可同时支持 -n 与 -r 的任意组合。
 * 选项解析用 while (--argc>0 && (*++argv)[0]=='-') 配合内层循环遍历
 * 每个选项字符。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

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

/* readlines: 读入所有输入行；返回行数，超限返回 -1 */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines = 0;
    char *p, line[MAXLEN];

    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
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

/* numcmp: 按数值比较 s1 与 s2 */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* qsort: 以递增或递减顺序对 v[left]..v[right] 排序 */
void qsort(void *v[], int left, int right,
           int (*comp)(const void *, const void *), int reverse)
{
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (reverse ? (*comp)(v[i], v[left]) > 0
                    : (*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1, comp, reverse);
    qsort(v, last + 1, right, comp, reverse);
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0, reverse = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (*++argv[0])
            switch (*argv[0]) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                printf("非法选项 %c\n", *argv[0]);
                break;
            }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void **)lineptr, 0, nlines - 1,
              (int (*)(const void *, const void *))(numeric ? numcmp : strcmp),
              reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("输入太大，无法排序\n");
        return 1;
    }
}
