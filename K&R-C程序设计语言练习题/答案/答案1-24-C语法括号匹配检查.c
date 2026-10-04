/*
 * 答案1-24 C语法括号匹配检查
 *
 * 提示：逐行检查：遇到 /* 跳过块注释；遇到单引号或双引号跳过字符串与字符常量（注意反斜杠转义会跳过下一个字符）；对 ( [ { 计数加一，对 ) ] } 计数减一，中途出现负数或行末计数不为 0 即报错。本程序按行处理，注释或字符串跨行时会有局限，但足以完成题述的基本检查。
 */
#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int checkline(char s[]);

/* check a C program for rudimentary syntax errors */
int main()
{
    char line[MAXLINE];
    int errors;

    errors = 0;
    while (getline(line, MAXLINE) > 0) {
        if (checkline(line) != 0) {
            printf("syntax error: %s", line);
            ++errors;
        }
    }
    if (errors == 0)
        printf("no syntax errors found\n");
    return errors != 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

/* checkline: check one line for unmatched (), [], {}; return 0 if ok */
int checkline(char s[])
{
    int i;
    int paren, brack, brace;
    int quote;

    paren = brack = brace = 0;
    for (i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '/' && s[i + 1] == '*') {
            /* skip a block comment */
            i += 2;
            while (s[i] != '\0' && !(s[i] == '*' && s[i + 1] == '/'))
                ++i;
            if (s[i] == '\0')
                break;              /* comment continues past line end */
            ++i;                    /* skip the closing '/' */
        } else if (s[i] == '\'' || s[i] == '"') {
            /* skip a quoted string or character constant */
            quote = s[i];
            ++i;
            while (s[i] != '\0' && s[i] != quote) {
                if (s[i] == '\\')
                    ++i;            /* skip the escaped character */
                ++i;
            }
            if (s[i] == '\0')
                break;              /* string continues past line end */
        } else {
            switch (s[i]) {
            case '(':
                ++paren;
                break;
            case ')':
                if (--paren < 0)
                    return -1;
                break;
            case '[':
                ++brack;
                break;
            case ']':
                if (--brack < 0)
                    return -1;
                break;
            case '{':
                ++brace;
                break;
            case '}':
                if (--brace < 0)
                    return -1;
                break;
            }
        }
    }
    if (paren != 0 || brack != 0 || brace != 0)
        return -1;
    return 0;
}
