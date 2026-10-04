/*
 * 答案1-20 detab制表符替换空格
 *
 * 提示：维护当前列位置 pos（从 1 开始计数）。遇到制表符时，计算到达下一个制表位（TABINC=8）所需空格数 nb = TABINC - (pos-1) % TABINC，连续输出 nb 个空格并更新 pos；遇到换行时重置 pos 为 1。n 用符号常量 TABINC 定义更清晰。
 */
#include <stdio.h>

#define TABINC 8    /* tab increment size */

/* detab: replace tabs with the proper number of blanks */
int main()
{
    int c, nb, pos;

    nb = 0;         /* number of blanks needed */
    pos = 1;        /* position in the line, starts at 1 */
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            nb = TABINC - (pos - 1) % TABINC;
            while (nb > 0) {
                putchar(' ');
                ++pos;
                --nb;
            }
        } else if (c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            ++pos;
        }
    }
    return 0;
}
