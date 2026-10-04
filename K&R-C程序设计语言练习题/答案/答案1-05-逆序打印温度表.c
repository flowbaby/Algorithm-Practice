/*
 * 答案1-05 逆序打印温度表
 *
 * 提示：把循环变量从上限 300 开始、按负步长递减到下限 0。用 for 循环更简洁：for (fahr = upper; fahr >= lower; fahr -= step)。注意用浮点数比较时要小心，但步长为 20 的整数序列不存在精度问题。
 */
#include <stdio.h>

/* print Fahrenheit-Celsius table in reverse order, from 300 to 0 */
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = upper;
    while (fahr >= lower) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr - step;
    }
    return 0;
}
