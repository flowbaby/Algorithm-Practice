/*
 * 答案1-08 统计空格制表符换行符
 *
 * 提示：用三个计数器分别统计空格 ' '、制表符 '\t'、换行符 '\n'，在 getchar() 循环里用三个独立的 if 分别判断累加（字符只会命中其一，用 if 链或并列 if 均可），最后打印三个计数。
 */
#include <stdio.h>

int main()
{
    int c, nb, nt, nl;

    nb = 0;     /* number of blanks */
    nt = 0;     /* number of tabs */
    nl = 0;     /* number of newlines */

    while ((c = getchar()) != EOF) {
        if (c == ' ')
            ++nb;
        if (c == '\t')
            ++nt;
        if (c == '\n')
            ++nl;
    }
    printf("%d %d %d\n", nb, nt, nl);
    return 0;
}
