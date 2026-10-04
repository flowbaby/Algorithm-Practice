/*
 * 练习1-05 逆序打印温度表
 *
 * 题目：修改温度转换程序，使之以逆序打印温度转换表，即从 300 度到 0 度。
 */
#include <stdio.h>

int main()
{
    double fahr, celsius;
    int lower, upper, step;

    lower = -100;
    upper = 200;
    step = 20;

    printf("摄氏度转华氏度对照表:\n");

    for (celsius = upper; celsius >= lower; celsius -= 20)
    {
        printf("%3.0lf\t%6.1lf\n", celsius, fahr);
    }

    return 0;
}