/*
 * 答案7-06 比较两个文件
 *
 * 提示：用 fgets 逐行读取两个文件并比较行内容：遇到第一个不同行时打印行号和两行内容并结束；若一个文件先读完而另一个还有内容，说明两个文件长度不同；都正常读到 EOF 则文件完全相同。注意处理打不开文件的错误并给出用法说明。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];
    char *s1, *s2;
    long lineno = 0;

    if (argc != 3) {
        fprintf(stderr, "usage: %s file1 file2\n", argv[0]);
        return 1;
    }
    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", argv[0], argv[1]);
        return 1;
    }
    if ((fp2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "%s: can't open %s\n", argv[0], argv[2]);
        fclose(fp1);
        return 1;
    }

    while ((s1 = fgets(line1, MAXLINE, fp1)) != NULL
        && (s2 = fgets(line2, MAXLINE, fp2)) != NULL) {
        lineno++;
        if (strcmp(line1, line2) != 0) {
            printf("两个文件在第 %ld 行首次不同：\n", lineno);
            printf("%s: %s", argv[1], line1);
            printf("%s: %s", argv[2], line2);
            fclose(fp1);
            fclose(fp2);
            return 0;
        }
    }

    if (s1 == NULL && s2 == NULL)
        printf("两个文件完全相同\n");
    else
        printf("两个文件不同：其中一个文件更长（较短者已于第 %ld 行结束）\n", lineno);
    fclose(fp1);
    fclose(fp2);
    return 0;
}
