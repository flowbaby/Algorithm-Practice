/*
 * 答案5-17 sort按字段排序
 *
 * 提示：为行内的字段排序需要先按空白把行拆成若干字段，再用 -k 选项
 * 指定字段范围（如 -k2,3n 表示第 2~3 个字段按数值排序，各字段可带
 * 独立的 n/f/d/r 选项）。比较函数 fieldcmp 通过全局字段选项 fo 先定位
 * 两行各自的字段子串，再按该字段的选项比较；若指定字段全部相同则返回 0。
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define MAXFIELDS 10

char *lineptr[MAXLINES];

/* 字段排序选项（全局，供比较函数使用） */
struct fieldopt {
    int start, end;     /* 字段范围（从 1 计） */
    int numeric, fold, dir, reverse;
};
struct fieldopt fo;

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

/* 把 s 的第 field 个字段的起止位置写入 *start、*end（含两端） */
void fieldpos(char *s, int field, int *start, int *end)
{
    int f = 1;
    char *p = s;

    *start = -1;
    *end = -1;
    while (*p) {
        while (*p && !isspace(*p)) {        /* 跳过单词 */
            if (f == field) {
                if (*start == -1)
                    *start = p - s;
                *end = p - s;
            }
            p++;
        }
        if (f >= field)
            break;
        while (*p && isspace(*p))           /* 跳过空白 */
            p++;
        f++;
    }
}

/* 把一行中第 field 个字段复制到 buf */
void fieldstr(char *s, int field, char *buf, int size)
{
    int start, end, len, i;

    fieldpos(s, field, &start, &end);
    if (start == -1) {
        buf[0] = '\0';
        return;
    }
    len = end - start + 1;
    if (len >= size)
        len = size - 1;
    for (i = 0; i < len; i++)
        buf[i] = s[start + i];
    buf[len] = '\0';
}

/* fieldcmp: 按 fo 指定的字段与选项比较两行 */
int fieldcmp(char *s1, char *s2)
{
    char f1[MAXLEN], f2[MAXLEN];
    int f, r;
    double v1, v2;

    for (f = fo.start; f <= fo.end; f++) {
        fieldstr(s1, f, f1, MAXLEN);
        fieldstr(s2, f, f2, MAXLEN);
        if (fo.numeric) {
            v1 = atof(f1);
            v2 = atof(f2);
            r = (v1 < v2) ? -1 : (v1 > v2) ? 1 : 0;
        } else {
            char *p1 = f1, *p2 = f2;
            char a, b;
            do {
                if (fo.dir) {
                    while (!isalnum(*p1) && *p1 != ' ' && *p1 != '\0')
                        p1++;
                    while (!isalnum(*p2) && *p2 != ' ' && *p2 != '\0')
                        p2++;
                }
                a = fo.fold ? tolower(*p1) : *p1;
                b = fo.fold ? tolower(*p2) : *p2;
                p1++;
                p2++;
                r = a - b;
            } while (a != '\0' && r == 0);
        }
        if (r != 0)
            return fo.reverse ? -r : r;
    }
    return 0;   /* 指定字段全部相同 */
}

void qsort(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1, comp);
    qsort(v, last + 1, right, comp);
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
    char *p;

    /* 默认：整行按字典序 */
    fo.start = 1;
    fo.end = MAXFIELDS;
    fo.numeric = fo.fold = fo.dir = fo.reverse = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        for (p = argv[0] + 1; *p; p++)
            switch (*p) {
            case 'k':               /* -kstart,end 或 -kstart */
                if (argc > 0) {
                    char *spec = *++argv;
                    char *comma;
                    argc--;
                    fo.start = atoi(spec);
                    comma = strchr(spec, ',');
                    fo.end = (comma != NULL) ? atoi(comma + 1) : fo.start;
                    if (fo.end < fo.start)
                        fo.end = fo.start;
                }
                break;
            case 'n':
                fo.numeric = 1;
                break;
            case 'f':
                fo.fold = 1;
                break;
            case 'd':
                fo.dir = 1;
                break;
            case 'r':
                fo.reverse = 1;
                break;
            default:
                printf("非法选项 %c\n", *p);
                break;
            }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void **)lineptr, 0, nlines - 1,
              (int (*)(void *, void *))fieldcmp);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("输入太大，无法排序\n");
        return 1;
    }
}
