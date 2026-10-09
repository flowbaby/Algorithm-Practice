/*
 * 答案6-04 按词频降序输出
 *
 * 提示：先用 6.5 节的二叉树统计每个单词的出现次数（节点加 count 字段），
 * 再把树中的（单词, 次数）对收集到数组，按次数降序排序后输出
 * "次数 单词"。收集与排序用中序遍历 + 快速排序即可，不需要额外结构。
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define MAXWORDS 10000
#define BUFSIZE 100

struct tnode {              /* 树节点 */
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct wpair {              /* 词频对 */
    char *word;
    int count;
};

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

/* getword: 取下一个单词（跳过注释与字符串） */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c == '/') {
        if ((d = getch()) == '/') {
            while ((c = getch()) != '\n' && c != EOF)
                ;
            if (c != EOF)
                ungetch(c);
            return getword(word, lim);
        } else if (d == '*') {
            int prev = 0;
            while ((c = getch()) != EOF) {
                if (prev == '*' && c == '/')
                    break;
                prev = c;
            }
            return getword(word, lim);
        } else {
            ungetch(d);
            return c;
        }
    }
    if (c == '"') {
        while ((c = getch()) != EOF && c != '"')
            if (c == '\\')
                getch();
        return getword(word, lim);
    }
    if (c == '\'') {
        while ((c = getch()) != EOF && c != '\'')
            if (c == '\\')
                getch();
        return getword(word, lim);
    }
    if (!isalpha(c) && c != '_')
        return c;
    *w++ = c;
    while (--lim > 0 && (isalnum(c = getch()) || c == '_'))
        *w++ = c;
    if (c != EOF)
        ungetch(c);
    *w = '\0';
    return word[0];
}

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strdup2(char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* addtree: 把单词加入树，出现则 count++ */
struct tnode *addtree(struct tnode *p, char *word)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup2(word);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(word, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, word);
    else
        p->right = addtree(p->right, word);
    return p;
}

/* collect: 中序遍历把树中词频对收集进数组 */
void collect(struct tnode *p, struct wpair *pairs, int *n)
{
    if (p != NULL) {
        collect(p->left, pairs, n);
        pairs[*n].word = p->word;
        pairs[*n].count = p->count;
        (*n)++;
        collect(p->right, pairs, n);
    }
}

/* 按次数降序比较（供 qsort 使用） */
int cmpcount(const void *a, const void *b)
{
    const struct wpair *x = (const struct wpair *)a;
    const struct wpair *y = (const struct wpair *)b;

    return y->count - x->count;     /* 降序 */
}

int main(void)
{
    struct tnode *root = NULL;
    struct wpair pairs[MAXWORDS];
    int n = 0, i;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    collect(root, pairs, &n);
    qsort(pairs, n, sizeof(struct wpair), cmpcount);
    for (i = 0; i < n; i++)
        printf("%4d %s\n", pairs[i].count, pairs[i].word);
    return 0;
}
