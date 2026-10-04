/*
 * 答案6-02 前6字符相同变量分组
 *
 * 提示：用练习 6-01 的改进 getword 收集 C 程序中的所有标识符（过滤掉
 * 常见 C 关键字），存入数组后按前 n 个字符排序分组；同组内若包含
 * 两个以上不同的完整名字则打印整组。n 由命令行参数给出，默认 6。
 * 字符串与注释内的单词已被 getword 跳过。
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define MAXWORDS 5000
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

/* getword: 改进版取词（处理下划线、注释、字符串、预处理行） */
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
    if (c == '#') {
        while ((c = getch()) != '\n' && c != EOF)
            ;
        if (c != EOF)
            ungetch(c);
        return getword(word, lim);
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

char *words[MAXWORDS];
int nwords = 0;

/* iskeyword: 判断是否为 C 关键字（过滤用） */
int iskeyword(char *s)
{
    static char *keys[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    int i;

    for (i = 0; i < (int)(sizeof keys / sizeof keys[0]); i++)
        if (strcmp(s, keys[i]) == 0)
            return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    char word[MAXWORD];
    int n = 6;          /* 前 n 个字符分组 */
    int i, j;

    if (argc > 1)
        n = atoi(argv[1]);
    if (n < 1)
        n = 6;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && !iskeyword(word) && nwords < MAXWORDS)
            words[nwords++] = strdup(word);

    /* 按完整单词字典序排序 */
    for (i = 0; i < nwords - 1; i++)
        for (j = i + 1; j < nwords; j++)
            if (strcmp(words[i], words[j]) > 0) {
                char *tmp = words[i];
                words[i] = words[j];
                words[j] = tmp;
            }

    /* 按前 n 个字符分组输出；组内多于一个不同单词时打印整组 */
    i = 0;
    while (i < nwords) {
        int start = i;
        while (i < nwords && strncmp(words[i], words[start], n) == 0)
            i++;
        if (i - start > 1) {        /* 组内至少两个不同的完整名字 */
            for (j = start; j < i; j++)
                printf("%s\n", words[j]);
            printf("\n");
        }
    }
    return 0;
}
