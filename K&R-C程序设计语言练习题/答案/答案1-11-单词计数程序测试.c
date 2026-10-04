/*
 * 答案1-11 单词计数程序测试
 *
 * 提示：完整解答——测试应覆盖以下输入：①空输入（无任何字符）；②只含空白字符（空格、制表符、换行）的输入；③行首或行尾带空格/制表符；④单词之间出现连续多个分隔符；⑤单词内部含数字或标点（程序把除空白外的所有字符都算作单词的一部分）；⑥最后一行没有末尾换行符；⑦极长的单词。最容易暴露 bug 的输入是：以空格开头或结尾的输入、连续多个分隔符、没有末尾换行符的输入，以及空输入——它们会暴露状态变量初值、边界判断（如最后一个单词是否被计数）等方面的问题。下面给出 1.5.4 节单词计数程序的原版演示代码，可按上述输入逐一测试。
 */
#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

/* count lines, words, and characters in input */
int main()
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
    return 0;
}
