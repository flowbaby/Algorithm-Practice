/*
 * 答案1-15 温度转换函数
 *
 * 提示：把换算公式封装成函数 float celsius(float fahr)，函数原型在使用前声明。主函数负责循环与输出，调用 celsius(fahr) 得到换算结果。注意函数内仍用 5.0/9.0 保证浮点除法。
 */
#include <stdio.h>

float celsius(float fahr);

/* print Fahrenheit-Celsius table using a function for conversion */
int main()
{
    float fahr;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;
    while (fahr <= upper) {
        printf("%3.0f %6.1f\n", fahr, celsius(fahr));
        fahr = fahr + step;
    }
    return 0;
}

/* celsius: convert fahr into celsius */
float celsius(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}
