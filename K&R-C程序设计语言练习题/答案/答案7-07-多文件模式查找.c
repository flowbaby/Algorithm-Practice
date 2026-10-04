/*
 * 答案7-07 多文件模式查找
 *
 * 提示：沿用第5章 find 的选项处理（-x 反向、-n 带行号），但把输入源扩展为命令行剩余参数中的一组文件；若没有文件参数则从标准输入读取。关于"是否打印文件名"：只有一个文件（或标准输入）时打印文件名没有意义，指定了多个文件时应打印文件名以区分匹配行来自哪个文件，故用文件个数决定是否打印。fgets 读行、strstr 判断子串出现。
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

/* getline: 读入一行，返回行长度，EOF 时返回 -1 */
int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return (c == EOF && i == 0) ? -1 : i;
}

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno;
    int c, except = 0, number = 0, found = 0;
    char *pattern;
    int print_name;    /* 指定了多个文件时才打印文件名 */

    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                fprintf(stderr, "find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
    if (argc < 1) {
        fprintf(stderr, "usage: find [-x] [-n] pattern [file ...]\n");
        return 2;
    }
    pattern = *argv;
    argc--;
    argv++;
    print_name = (argc > 1);

    if (argc == 0) {              /* 无文件参数：读标准输入 */
        lineno = 0;
        while (getline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, pattern) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }
    } else {
        while (argc-- > 0) {
            FILE *fp;
            if ((fp = fopen(*argv, "r")) == NULL) {
                fprintf(stderr, "find: can't open %s\n", *argv);
                continue;
            }
            lineno = 0;
            while (fgets(line, MAXLINE, fp) != NULL) {
                lineno++;
                if ((strstr(line, pattern) != NULL) != except) {
                    if (print_name)
                        printf("%s:", *argv);
                    if (number)
                        printf("%ld:", lineno);
                    printf("%s", line);
                    found++;
                }
            }
            fclose(fp);
            argv++;
        }
    }
    return found;
}
