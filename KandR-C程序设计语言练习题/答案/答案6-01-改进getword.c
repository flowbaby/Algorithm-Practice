/*
 * 答案6-01 改进getword
 *
 * 提示：改进的 getword 在取词前先识别并跳过——下划线作为标识符的合法
 * 首字符（与字母同等对待）；"//" 行注释与块注释两类注释；"..." 字符串
 * 常量与 '...' 字符常量（注意转义符 \）；以 # 开头的预处理控制行整行
 * 跳过。上述情况都通过递归调用 getword 继续取下一个单词，非单词字符
 * 则作为单字符标记直接返回。程序主体用 6.3 节的单词计数例子演示。
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getword: 从输入中取下一个单词或字符（改进版） */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c == '/') {                     /* 注释 */
        if ((d = getch()) == '/') {     /* "//" 行注释 */
            while ((c = getch()) != '\n' && c != EOF)
                ;
            if (c != EOF)
                ungetch(c);
            return getword(word, lim);
        } else if (d == '*') {          /* 块注释：读到 "*" + "/" 结束 */
            int prev = 0;
            while ((c = getch()) != EOF) {
                if (prev == '*' && c == '/')
                    break;
                prev = c;
            }
            return getword(word, lim);
        } else {
            ungetch(d);
            return c;                   /* 单独的 '/' */
        }
    }
    if (c == '#') {                     /* 预处理控制行 */
        while ((c = getch()) != '\n' && c != EOF)
            ;
        if (c != EOF)
            ungetch(c);
        return getword(word, lim);
    }
    if (c == '"') {                     /* 字符串常量 */
        while ((c = getch()) != EOF && c != '"')
            if (c == '\\')              /* 跳过转义字符 */
                getch();
        return getword(word, lim);
    }
    if (c == '\'') {                    /* 字符常量 */
        while ((c = getch()) != EOF && c != '\'')
            if (c == '\\')
                getch();
        return getword(word, lim);
    }
    if (!isalpha(c) && c != '_')
        return c;                       /* 非单词字符 */
    *w++ = c;
    while (--lim > 0 && (isalnum(c = getch()) || c == '_'))
        *w++ = c;
    if (c != EOF)
        ungetch(c);
    *w = '\0';
    return word[0];
}

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    {"int", 0},
    {"char", 0},
    {"void", 0},
    {"return", 0},
    {"if", 0},
    {"else", 0}
};

#define NKEYS (sizeof keytab / sizeof keytab[0])

int binsearch(char *word, struct key tab[], int n)
{
    int cond, low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int main(void)
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}
