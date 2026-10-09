/*
 * 答案1-02 转义字符实验
 *
 * 提示：\c 不是 C 语言定义的合法转义序列。多数编译器（如 GCC）会给出 "unknown escape sequence" 之类的警告，然后把 \c 当作普通字符 c 输出；少数编译器会直接报错。运行本程序观察你所用编译器的警告信息与输出结果，即可了解未列出的 \c 的处理方式。
 */
#include <stdio.h>

int main()
{
    printf("hello, world\c\n");
    return 0;
}
