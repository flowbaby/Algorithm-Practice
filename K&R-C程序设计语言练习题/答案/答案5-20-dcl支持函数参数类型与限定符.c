/*
 * 答案5-20 dcl支持函数参数类型与限定符
 *
 * 提示：在 5.12 节 dcl 基础上做两处扩展——(1) gettoken 遇到 '(' 且括号
 * 内非空时，把整个参数列表（含括号）读入 token 作为 PARENS 标记，
 * 输出时写为 "function taking (参数列表) returning"；(2) 主循环把
 * const/volatile/unsigned/long/struct 等类型词与限定符连续收集到
 * datatype 中，再交给 dcl 解析声明符。
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

int errflag = 0;

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

void errmsg(char *msg)
{
    printf("%s\n", msg);
    errflag = 1;
}

/* gettoken: 返回下一个标记；函数参数列表整体作为一个 PARENS 标记 */
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
            /* 读入整个参数列表（括号嵌套计数），存入 token */
            int depth = 1;
            *p++ = '(';
            *p++ = c;
            while (depth > 0 && (c = getch()) != EOF) {
                if (c == '(')
                    depth++;
                else if (c == ')')
                    depth--;
                if (depth == 0)
                    break;
                if (p < token + MAXTOKEN - 1)
                    *p++ = c;
            }
            *p++ = ')';
            *p = '\0';
            return tokentype = PARENS;
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

/* istype: 判断 token 是否类型词或限定符 */
int istype(char *s)
{
    static char *types[] = {
        "char", "int", "float", "double", "void", "short", "long",
        "signed", "unsigned", "struct", "enum", "union",
        "const", "volatile", "static", "extern", "register", "typedef"
    };
    int i;

    for (i = 0; i < (int)(sizeof(types) / sizeof(types[0])); i++)
        if (strcmp(s, types[i]) == 0)
            return 1;
    return 0;
}

void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; )
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

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
        if (type == PARENS) {
            if (token[1] != ')') {      /* 非空参数列表 */
                strcat(out, " function taking");
                strcat(out, token);
            } else
                strcat(out, " function returning");
        } else {
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
        /* 连续收集类型词与限定符到 datatype */
        while (tokentype == NAME && istype(token)) {
            strcat(datatype, " ");
            strcat(datatype, token);
            gettoken();
        }
        out[0] = '\0';
        name[0] = '\0';
        errflag = 0;
        /* 此时 tokentype 已是声明符的第一个标记 */
        dcl();
        if (errflag || (tokentype != '\n' && tokentype != EOF)) {
            printf("syntax error\n");
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
