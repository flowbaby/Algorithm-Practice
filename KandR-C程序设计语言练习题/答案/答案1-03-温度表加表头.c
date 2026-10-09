/*
 * 答案1-03 温度表加表头
 *
 * 提示：在进入 while 循环之前先调用一次 printf 打印表头（如 "Fahr Celsius"）。表头各列之间留一个空格，与数据行的 %3.0f 和 %6.1f 输出宽度对齐，使表格整齐美观。
 */
#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300 */
int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    printf("Fahr Celsius\n");
    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}
