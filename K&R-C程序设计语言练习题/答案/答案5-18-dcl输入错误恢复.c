/*
 * 答案5-18 dcl输入错误恢复
 *
 * 提示：原版 dcl 在语法错误时直接退出程序；本版本把"报错并退出"改为
 * 设置错误标志 errmsg 后跳过本行剩余输入，继续解析下一行声明。
 * 解析器仍沿用 5.12 节的 dcl/dirdcl/gettoken 结构，主循环负责
 * 错误恢复与状态重置。
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS };

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

char buf[BUFSIZE];
int bufp = 0;

int errflag = 0;        /* 出错标志：出错后跳过本行剩余输入 */

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

/* errmsg: 打印错误并设置错误标志 */
void errmsg(char *msg)
{
    printf("%s\n", msg);
    errflag = 1;
}

/* gettoken: 返回下一个标记 */
int gettoken(void)
{
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

/* dcl: 解析一个声明符 */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; )
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: 解析声明符的其余部分 */
void dirdcl(void)
{
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            errmsg("error: missing )");
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        errmsg("error: expected name or (dcl)");

    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

int main(void)
{
    int c;

    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        name[0] = '\0';
        errflag = 0;
        dcl();
        if (errflag || (tokentype != '\n' && tokentype != EOF)) {
            printf("syntax error\n");
            /* 跳过本行剩余输入，恢复状态 */
            while ((c = getch()) != '\n' && c != EOF)
                ;
            if (c == EOF)
                break;
            continue;
        }
        if (name[0] == '\0')
            strcpy(name, "?");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}
