/*
 * 答案1-06 验证getchar不等于EOF
 *
 * 提示：表达式 getchar() != EOF 的结果只能是 0 或 1。把该表达式赋给 int 变量并循环打印：读到普通字符时表达式为真（1），读到 EOF 时为假（0）。注意 getchar 返回 int，且 != 优先级高于 =，写成 c = (getchar() != EOF) 更清晰。
 */
#include <stdio.h>

/* verify that the expression getchar() != EOF is 0 or 1 */
int main()
{
    int c;

    while (c = (getchar() != EOF)) {
        printf("%d\n", c);
    }
    printf("%d - at EOF\n", c);
    return 0;
}
