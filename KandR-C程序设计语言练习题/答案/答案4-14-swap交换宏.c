/*
 * 答案4-14 swap交换宏
 *
 * 提示：宏 swap(t,x,y) 用块结构 { ... } 包裹，内部声明一个类型为 t 的局部变量
 * 作中转，依次完成 x=y、y=临时值 的交换。块结构使宏可以安全用在 if/else
 * 等语句中而不会出现悬空 else 问题；使用时要保证 x、y 是可修改的左值，
 * 且局部变量名（如 _z）不与调用处的名字冲突。
 */
#include <stdio.h>

#define swap(t, x, y)  { t _z; _z = x; x = y; y = _z; }

int main(void)
{
    int x = 1, y = 2;
    double a = 1.5, b = 2.5;
    char *p = "one", *q = "two";

    swap(int, x, y);
    printf("x = %d, y = %d\n", x, y);

    swap(double, a, b);
    printf("a = %g, b = %g\n", a, b);

    swap(char *, p, q);
    printf("p = %s, q = %s\n", p, q);

    /* 在 if 中使用宏也不会出错 */
    if (x > y)
        swap(int, x, y);
    else
        printf("x <= y\n");
    printf("x = %d, y = %d\n", x, y);

    return 0;
}
