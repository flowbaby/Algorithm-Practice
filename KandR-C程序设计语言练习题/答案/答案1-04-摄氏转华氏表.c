/*
 * 答案1-04 摄氏转华氏表
 *
 * 提示：与 1.2 节的华氏转摄氏表对称：把循环变量改为摄氏温度，用公式 fahr = 9.0/5.0 * celsius + 32.0 换算，再按相应格式输出。注意除法用 9.0/5.0 而不是 9/5，避免整数除法截断。
 */
#include <stdio.h>

/* print Celsius-Fahrenheit table for celsius = 0, 20, ..., 300 */
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    celsius = lower;
    while (celsius <= upper) {
        fahr = (9.0 / 5.0) * celsius + 32.0;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return 0;
}
