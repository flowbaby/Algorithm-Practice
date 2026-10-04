/*
 * 答案1-12 每行输出一个单词
 *
 * 提示：复用单词计数的 IN/OUT 状态思想。处于单词内时逐字符输出；遇到空白分隔符且刚从单词内出来时，输出一个换行并回到 OUT 状态。这样每个单词独占一行。
 */
#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

int main()
{
    int c, state;

    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                putchar('\n');
                state = OUT;
            }
        } else {
            state = IN;
            putchar(c);
        }
    }
    return 0;
}
