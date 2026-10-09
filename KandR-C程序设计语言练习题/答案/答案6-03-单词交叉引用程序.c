/*
 * 答案6-03 单词交叉引用程序
 *
 * 提示：用 6.5 节的二叉树组织单词，每个单词节点挂一个行号链表，记录
 * 该单词出现的所有行号。getword 维护全局行号 lineno（读到 '\n' 时自增），
 * 并跳过字符串、注释与预处理行。输出前用 treeprint 中序遍历（字典序），
 * 每词一行，后跟所有行号；"the"、"and" 等噪声词不收录。
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

struct lnode {              /* 行号链表 */
    int line;
    struct lnode *next;
};

struct tnode {              /* 树节点 */
    char *word;
    struct lnode *lines;
    struct tnode *left;
    struct tnode *right;
};

char buf[BUFSIZE];
int bufp = 0;
int lineno = 1;             /* 当前行号 */

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

/* getword: 改进版取词，同时维护 lineno */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    while (isspace(c = getch()))
        if (c == '\n')
            lineno++;
    if (c == '/') {
        if ((d = getch()) == '/') {
            while ((c = getch()) != '\n' && c != EOF)
                ;
            if (c != EOF) {
                ungetch(c);
                lineno++;
            }
            return getword(word, lim);
        } else if (d == '*') {
            int prev = 0;
            while ((c = getch()) != EOF) {
                if (c == '\n')
                    lineno++;
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
    if (c == '#') {
        while ((c = getch()) != '\n' && c != EOF)
            ;
        if (c != EOF) {
            ungetch(c);
            lineno++;
        }
        return getword(word, lim);
    }
    if (c == '"') {
        while ((c = getch()) != EOF && c != '"')
            if (c == '\\')
                getch();
            else if (c == '\n')
                lineno++;
        return getword(word, lim);
    }
    if (c == '\'') {
        while ((c = getch()) != EOF && c != '\'')
            if (c == '\\')
                getch();
            else if (c == '\n')
                lineno++;
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

/* addline: 把行号 ln 加入节点的行号链表（去重） */
struct lnode *addline(struct lnode *list, int ln)
{
    struct lnode *p;

    for (p = list; p != NULL; p = p->next)
        if (p->line == ln)
            return list;
    p = (struct lnode *)malloc(sizeof(struct lnode));
    p->line = ln;
    p->next = list;
    return p;
}

/* addtree: 把单词 word 及其行号 ln 加入树 */
struct tnode *addtree(struct tnode *p, char *word, int ln)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup2(word);
        p->lines = addline(NULL, ln);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(word, p->word)) == 0)
        p->lines = addline(p->lines, ln);
    else if (cond < 0)
        p->left = addtree(p->left, word, ln);
    else
        p->right = addtree(p->right, word, ln);
    return p;
}

/* treeprint: 中序遍历打印树 */
void treeprint(struct tnode *p)
{
    struct lnode *lp;

    if (p != NULL) {
        treeprint(p->left);
        printf("%s:", p->word);
        for (lp = p->lines; lp != NULL; lp = lp->next)
            printf(" %d", lp->line);
        printf("\n");
        treeprint(p->right);
    }
}

/* noise: 判断是否为噪声词 */
int noise(char *w)
{
    static char *nw[] = {
        "a", "an", "and", "are", "as", "at", "be", "by", "for",
        "from", "in", "is", "it", "of", "on", "or", "that", "the",
        "this", "to", "was", "were", "with"
    };
    int i;

    for (i = 0; i < (int)(sizeof nw / sizeof nw[0]); i++)
        if (strcmp(w, nw[i]) == 0)
            return 1;
    return 0;
}

int main(void)
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && !noise(word))
            root = addtree(root, word, lineno);
    treeprint(root);
    return 0;
}
