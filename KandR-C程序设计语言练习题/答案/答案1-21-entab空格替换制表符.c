/*
 * 答案1-21 entab空格替换制表符
 *
 * 提示：连续数空格 nb，每当空格落在制表位（pos % TABINC == 0）时，把已数出的空格折合成一个制表符（++nt，nb=0）；遇到非空格字符时先输出积攒的 nt 个制表符和 nb 个空格，再输出该字符。pos 在读取空格时同步推进（空格虽被缓存，但占据相应列），输出缓存空格时不再重复计数，从而保证制表位判断与列位置一致。
 */
#include <stdio.h>

#define TABINC 8    /* tab increment size */

/* entab: replace strings of blanks with tabs and blanks */
int main()
{
    int c, nb, nt, pos;

    nb = 0;         /* number of pending blanks */
    nt = 0;         /* number of pending tabs */
    pos = 1;        /* column of the next output character, starts at 1 */

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++nb;
            if (pos % TABINC == 0) {    /* this blank lands on a tab stop */
                ++nt;                   /* fold the blank run into one tab */
                nb = 0;
            }
            ++pos;      /* blanks are buffered but occupy these columns */
        } else {
            while (nt > 0) {
                putchar('\t');
                --nt;
            }
            while (nb > 0) {
                putchar(' ');
                --nb;
            }
            putchar(c);
            if (c == '\n')
                pos = 1;
            else
                ++pos;
        }
    }
    return 0;
}
