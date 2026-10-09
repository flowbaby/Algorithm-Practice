/*
 * 答案5-11 命令行指定制表位
 *
 * 提示：detab 把制表符展开为空格——遇到 '\t' 时补空格直到下一个制表位；
 * entab 相反，把到达制表位的连续空格替换为 '\t'。命令行参数给出制表位
 * 列表（列号，可多个），无参数时用默认的每 8 列。nextstop 根据当前列
 * 计算下一个制表位，超过最后一个制表位后按最后两个制表位的间隔扩展。
 * 第一个参数 -e 选择 entab 模式，-d 或不给参数则默认 detab 模式。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTABS 100
#define DEFAULT 8

int tabs[MAXTABS];      /* 制表位列表 */
int ntabs = 0;          /* 制表位个数 */

/* settabs: 从命令行读取制表位；无参数时使用默认设置 */
void settabs(int argc, char *argv[])
{
    int i;

    if (argc <= 1)
        return;
    for (i = 1; i < argc && ntabs < MAXTABS; i++)
        tabs[ntabs++] = atoi(argv[i]);
}

/* nextstop: 返回 col 之后的下一个制表位位置 */
int nextstop(int col)
{
    int i;

    if (ntabs == 0)
        return ((col / DEFAULT) + 1) * DEFAULT;
    for (i = 0; i < ntabs; i++)
        if (tabs[i] > col)
            return tabs[i];
    /* 超过最后一个制表位：按最后两个制表位的间隔扩展 */
    return col + (tabs[ntabs - 1] - tabs[ntabs - 2]);
}

/* detab: 把制表符展开为空格 */
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

/* entab: 把到达制表位的连续空格替换为制表符 */
void entab(void)
{
    int c, col = 0, nb = 0;     /* nb：连续空格计数 */

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (col == nextstop(col) - 1) { /* 该空格恰好到达制表位 */
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

    if (argc > 1 && strcmp(argv[1], "-e") == 0) {
        entab_mode = 1;
        argc--;
        argv++;
    } else if (argc > 1 && strcmp(argv[1], "-d") == 0) {
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
