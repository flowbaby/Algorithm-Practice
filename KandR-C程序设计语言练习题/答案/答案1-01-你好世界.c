/*
 * 答案1-01 你好世界
 *
 * 提示：运行"hello, world"程序，确认输出 hello, world。然后尝试去掉各部分观察编译错误：去掉 #include <stdio.h> 会得到 printf 未声明的警告/错误；去掉 main 后的括号会报函数定义错误；去掉分号会报语法错误；去掉 return 0 程序仍可运行但无返回值。通过反复删改，理解每个语法元素的作用。
 */
#include <stdio.h>

int main()
{
    printf("hello, world\n");
    return 0;
}
