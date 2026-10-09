/*
 * 答案1-14 字符频率直方图
 *
 * 提示：用一个大小 128 的 int 数组统计每个字符的出现次数（读入的字符作下标），统计完成后找出最大值做归一化，再对出现次数大于 0 的字符打印直方图。用 isprint 判断字符是否可打印，以便在横条前标注字符本身。
 */
#include <stdio.h>
#include <ctype.h>

#define MAXHIST 15  /* max length of histogram */
#define MAXCHAR 128 /* max number of different characters */

/* print horizontal histogram of character frequencies */
int main()
{
    int c, i;
    int len;            /* length of each bar */
    int maxvalue;       /* maximum value for cc[] */
    int cc[MAXCHAR];    /* character counters */

    for (i = 0; i < MAXCHAR; ++i)
        cc[i] = 0;

    while ((c = getchar()) != EOF)
        if (c < MAXCHAR)
            ++cc[c];

    maxvalue = 0;
    for (i = 1; i < MAXCHAR; ++i)
        if (cc[i] > maxvalue)
            maxvalue = cc[i];

    for (i = 1; i < MAXCHAR; ++i) {
        if (cc[i] > 0) {
            if (isprint(i))
                printf("%5d - %c - %5d : ", i, i, cc[i]);
            else
                printf("%5d -   - %5d : ", i, cc[i]);
            len = cc[i] * MAXHIST / maxvalue;
            if (len <= 0)
                len = 1;
            while (len > 0) {
                putchar('*');
                --len;
            }
            putchar('\n');
        }
    }
    return 0;
}
