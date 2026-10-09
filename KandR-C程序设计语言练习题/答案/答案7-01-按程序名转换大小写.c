/*
 * 答案7-01 按程序名转换大小写
 *
 * 提示：程序的行为由 argv[0] 决定：把程序复制/链接成名为 lower（或含 lower）的可执行文件调用时执行大写转小写，名为 upper 时执行小写转大写。使用函数指针 int (*conv)(int) 在两种转换函数间选择，用 strrchr 去掉路径前缀、strstr 判断名字中的关键字，与标准 getchar/putchar 循环配合即可。
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int c;
    int (*conv)(int) = NULL;   /* 函数指针：指向 tolower 或 toupper */
    char *base;

    if (argc > 0) {
        base = strrchr(argv[0], '\\');   /* Windows 路径分隔符 */
        if (base == NULL)
            base = strrchr(argv[0], '/');  /* UNIX 路径分隔符 */
        base = (base == NULL) ? argv[0] : base + 1;

        if (strstr(base, "lower") != NULL)
            conv = tolower;
        else if (strstr(base, "upper") != NULL)
            conv = toupper;
    }
    if (conv == NULL) {
        fprintf(stderr, "usage: 本程序应被命名为 lower 或 upper 后调用\n");
        return 1;
    }
    while ((c = getchar()) != EOF)
        putchar(conv(c));
    return 0;
}
