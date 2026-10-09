/*
 * 答案5-12 制表位简写参数-m+n
 *
 * 提示：参数 -m 表示起始列 m，+n 表示制表位间隔 n 列，即制表位位于
 * m, m+n, m+2n, ...。无参数时默认行为取起始列 0、间隔 8（即每 8 列）。
 * entab 与 detab 共用同一个 nextstop 计算逻辑，只是处理空白的方向相反。
 */
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_START 0
#define DEFAULT_INT 8

int start = DEFAULT_START;      /* 起始列 */
int interval = DEFAULT_INT;     /* 制表位间隔 */

/* settabs: 解析 -m 与 +n 参数；无参数时保持默认 */
void settabs(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-')
            start = atoi(argv[i] + 1);
        else if (argv[i][0] == '+')
            interval = atoi(argv[i] + 1);
        else
            printf("未知参数：%s\n", argv[i]);
    }
    if (interval < 1)
        interval = DEFAULT_INT;
}

/* nextstop: 返回 col 之后的下一个制表位位置 */
int nextstop(int col)
{
    int stop = start;

    while (stop <= col)
        stop += interval;
    return stop;
}

/* detab：把制表符展开为空格 */
void detab(void)
{
    int c, col = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int stop = nextstop(col);
            do {
                putchar(' ');
                col++;
            } while (col < stop);
        } else if (c == '\n') {
            putchar(c);
            col = 0;
        } else {
            putchar(c);
            col++;
        }
    }
}

/* entab：把连续的若干空格在制表位处替换为制表符 */
void entab(void)
{
    int c, col = 0, nb = 0;     /* nb：连续空格计数 */

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (col == nextstop(col) - 1) { /* 当前列正好是制表位前一列 */
                putchar('\t');
                col = nextstop(col);
                nb = 0;
            } else {
                nb++;
                col++;
            }
        } else if (c == '\n') {
            while (nb-- > 0)
                putchar(' ');
            putchar(c);
            col = 0;
            nb = 0;
        } else {
            while (nb-- > 0)
                putchar(' ');
            putchar(c);
            col++;
            nb = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    int entab_mode = 0;

    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'e') {
        entab_mode = 1;
        argc--;
        argv++;
    }
    settabs(argc, argv);
    if (entab_mode)
        entab();
    else
        detab();
    return 0;
}
