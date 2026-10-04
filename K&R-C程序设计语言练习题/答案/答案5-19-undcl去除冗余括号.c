/*
 * 答案5-19 undcl去除冗余括号
 *
 * 提示：undcl 把文字描述（如 "x pointer to function returning int"）
 * 反向转换回声明形式。原版遇到 '*' 时无条件写成 "(*%s)"，即使 out
 * 只是单个名字也会产生冗余括号。修改为：仅当 out 是复合表达式
 * （含空格或已含括号）时才加括号，单个名字直接拼 "*name"。
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char out[1000];

/* gettoken: 返回下一个标记 */
int gettoken(void)
{
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getchar()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

/* 判断 out 是否为复合表达式（需要加括号） */
int needs_parens(char *s)
{
    return (strchr(s, ' ') != NULL || strchr(s, '(') != NULL);
}

int main(void)
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n' && type != EOF)
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                if (needs_parens(out))
                    sprintf(temp, "(*%s)", out);
                else
                    sprintf(temp, "*%s", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        printf("%s\n", out);
    }
    return 0;
}
