/*
 * 答案5-16 sort目录序d
 *
 * 提示：在 charcmp 中增加 -d 处理——比较前先跳过非字母、非数字、
 * 非空白的字符，只对字母、数字和空白进行比较；-f 的 tolower 折叠
 * 与 -d 的跳过相互独立，可以同时启用（先折叠后跳过或先跳过再折叠
 * 均可，本实现先跳过再折叠，结果一致）。
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];
int fold = 0;           /* -f：忽略大小写 */
int dir = 0;            /* -d：目录序 */

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

void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

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

/* charcmp: 字符比较，支持 -f（忽略大小写）与 -d（只比较字母数字空白） */
int charcmp(const char *s1, const char *s2)
{
    char a, b;

    do {
        if (dir) {                  /* 跳过不参与比较的字符 */
            while (!isalnum(*s1) && *s1 != ' ' && *s1 != '\0')
                s1++;
            while (!isalnum(*s2) && *s2 != ' ' && *s2 != '\0')
                s2++;
        }
        a = fold ? tolower(*s1) : *s1;
        b = fold ? tolower(*s2) : *s2;
        s1++;
        s2++;
        if (a == b)
            continue;
        return a - b;
    } while (a != '\0');
    return 0;
}

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
            case 'f':
                fold = 1;
                break;
            case 'd':
                dir = 1;
                break;
            default:
                printf("非法选项 %c\n", *argv[0]);
                break;
            }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void **)lineptr, 0, nlines - 1,
              (int (*)(const void *, const void *))(numeric ? numcmp : charcmp),
              reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("输入太大，无法排序\n");
        return 1;
    }
}
