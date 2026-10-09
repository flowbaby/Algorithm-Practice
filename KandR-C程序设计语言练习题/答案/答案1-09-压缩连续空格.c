/*
 * 答案1-09 压缩连续空格
 *
 * 提示：用一个标志 inspace 记录"当前是否处于连续空格中"。遇到空格时，只在 inspace 为假时输出一个空格并置真；遇到非空格字符时输出该字符并把 inspace 置假。这样连续多个空格只输出第一个。
 */
#include <stdio.h>

int main()
{
    int c;
    int inspace;

    inspace = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (!inspace) {
                inspace = 1;
                putchar(c);
            }
        } else {
            inspace = 0;
            putchar(c);
        }
    }
    return 0;
}
