/*
 * 答案7-02 任意输入合理打印
 *
 * 提示：逐字符读入，用 isprint 区分图形字符与非图形字符：图形字符直接输出，非图形字符按八进制转义形式 \ooo 输出（每字符占 4 个字符宽度）。维护当前行输出位置，当行长超过限制（如 100）时插入换行，从而断开过长文本行；真正的换行符则原样输出并复位行位置。
 */
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100   /* 一行最多允许的字符数 */

int main(void)
{
    int c, pos = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar('\n');
            pos = 0;
        } else if (isprint(c)) {
            if (pos >= MAXLINE) {
                putchar('\n');
                pos = 0;
            }
            putchar(c);
            pos++;
        } else {
            if (pos + 4 >= MAXLINE) {   /* 转义形式本身占 4 个字符 */
                putchar('\n');
                pos = 0;
            }
            printf("\\%03o", c);
            pos += 4;
        }
    }
    return 0;
}
