/*
 * 答案6-06 简单define预处理器
 *
 * 提示：基于 6.6 节的 lookup/install 表实现无参数的 #define 处理器：
 * 逐字符读入，读到 '#' 时识别 #define，把宏名与宏体（该行剩余部分）
 * 存入表；读到普通标识符（字母或下划线开头）时查表，命中则输出替换
 * 文本，未命中则原样输出。非 define 的预处理行原样输出。getch/ungetch
 * 用于缓冲字符，使标识符读取与替换输出互不干扰。
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD 100
#define BUFSIZE 100

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

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

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *)np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* getword: 读取下一个单词（字母数字下划线序列），不跳过空白之外处理 */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c == EOF)
        return EOF;
    *w++ = c;
    while (--lim > 0 && (isalnum(c = getch()) || c == '_'))
        *w++ = c;
    if (c != EOF)
        ungetch(c);
    *w = '\0';
    return word[0];
}

int main(void)
{
    int c, d;
    char word[MAXWORD], defn[MAXWORD];

    while ((c = getch()) != EOF) {
        if (c == '#') {                 /* 预处理行 */
            if (getword(word, MAXWORD) != EOF && strcmp(word, "define") == 0) {
                if (getword(word, MAXWORD) != EOF) {    /* 宏名 */
                    char *p = defn;
                    /* 取宏体：去掉前导空白，直到行尾 */
                    while ((d = getch()) == ' ' || d == '\t')
                        ;
                    while (d != '\n' && d != EOF) {
                        if (p < defn + MAXWORD - 1)
                            *p++ = d;
                        d = getch();
                    }
                    *p = '\0';
                    install(word, defn);
                    if (d == '\n')
                        putchar('\n');
                }
            } else {
                /* 其他预处理行：原样输出 */
                putchar('#');
                printf("%s", word);
                while ((c = getch()) != '\n' && c != EOF)
                    putchar(c);
                if (c == '\n')
                    putchar('\n');
            }
        } else if (isalpha(c) || c == '_') {    /* 标识符 */
            struct nlist *np;
            char *p = word;

            *p++ = c;
            while (isalnum(c = getch()) || c == '_')
                if (p < word + MAXWORD - 1)
                    *p++ = c;
            *p = '\0';
            ungetch(c);
            if ((np = lookup(word)) != NULL)
                printf("%s", np->defn);         /* 替换 */
            else
                printf("%s", word);
        } else
            putchar(c);
    }
    return 0;
}
