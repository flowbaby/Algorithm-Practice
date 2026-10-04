/*
 * 答案7-08 分页打印多文件
 *
 * 提示：把每个文件打印到独立的一"页"上：用换页符 \f 开始新页，页首打印文件名标题和页码；每页固定行数（如 60 行），行数满一页后输出下一个 \f 并递增页码。文件打不开时打印错误并继续处理其余文件，无参数时读标准输入。
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define LINES_PER_PAGE 60   /* 每页行数 */

/* fileprint: 打印一个文件，从新页开始，带标题和页码 */
void fileprint(FILE *fp, char *fname)
{
    char line[MAXLINE];
    long lineno = 0;
    int page = 1;

    printf("\f%s  page %d\n\n", fname, page);
    while (fgets(line, MAXLINE, fp) != NULL) {
        if (++lineno > 1 && (lineno - 1) % LINES_PER_PAGE == 0) {
            page++;
            printf("\f%s  page %d\n\n", fname, page);
        }
        fputs(line, stdout);
    }
}

int main(int argc, char *argv[])
{
    int i;

    if (argc == 1) {
        fileprint(stdin, "stdin");
    } else {
        for (i = 1; i < argc; i++) {
            FILE *fp;
            if ((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", argv[0], argv[i]);
                continue;
            }
            fileprint(fp, argv[i]);
            fclose(fp);
        }
    }
    return 0;
}
