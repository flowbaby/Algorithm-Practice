/*
 * 答案1-13 单词长度直方图
 *
 * 提示：用数组 wl[i] 统计长度为 i 的单词个数（长度上限 MAXWORD，超长单词计入溢出计数）。打印时先找出最大值 maxvalue，把每个计数按 MAXHIST/maxvalue 归一化成横条长度，每行用 * 打印。垂直方向版本可先求最大高度，再从上到下逐行判断每个长度是否该画 *，更考验数组与循环的组织。
 */
#include <stdio.h>

#define MAXHIST 15  /* max length of histogram */
#define MAXWORD 11  /* max length of a word */
#define IN  1
#define OUT 0

/* print horizontal histogram of word lengths */
int main()
{
    int c, i, nc, state;
    int len;            /* length of each bar */
    int maxvalue;       /* maximum value for wl[] */
    int ovflow;         /* number of overflow words */
    int wl[MAXWORD];    /* word length counters */

    state = OUT;
    nc = 0;
    ovflow = 0;
    for (i = 0; i < MAXWORD; ++i)
        wl[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            state = OUT;
            if (nc > 0) {
                if (nc < MAXWORD)
                    ++wl[nc];
                else
                    ++ovflow;
            }
            nc = 0;
        } else if (state == OUT) {
            state = IN;
            nc = 1;
        } else {
            ++nc;
        }
    }
    if (nc > 0) {       /* last word, no terminator seen */
        if (nc < MAXWORD)
            ++wl[nc];
        else
            ++ovflow;
    }

    maxvalue = 0;
    for (i = 1; i < MAXWORD; ++i)
        if (wl[i] > maxvalue)
            maxvalue = wl[i];

    for (i = 1; i < MAXWORD; ++i) {
        printf("%5d - %5d : ", i, wl[i]);
        if (wl[i] > 0) {
            len = wl[i] * MAXHIST / maxvalue;
            if (len <= 0)
                len = 1;
        } else {
            len = 0;
        }
        while (len > 0) {
            putchar('*');
            --len;
        }
        putchar('\n');
    }
    if (ovflow > 0)
        printf("There are %d words >= %d\n", ovflow, MAXWORD);
    return 0;
}
