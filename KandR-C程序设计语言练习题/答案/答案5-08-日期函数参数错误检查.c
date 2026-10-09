/*
 * 答案5-08 日期函数参数错误检查
 *
 * 提示：在 day_of_year 中检查月份是否在 1~12 之间、日号是否在该月
 * 天数之内；在 month_day 中先算出全年总天数，再检查 yearday 是否越界。
 * 出错时打印错误信息并返回 -1（day_of_year）或把 *pmonth、*pday 置为 -1。
 * 闰年判断 (year%4==0 && year%100!=0) || year%400==0 保持不变。
 */
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: 根据年、月、日计算一年中的第几天；出错返回 -1 */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (year < 1 || month < 1 || month > 12) {
        printf("day_of_year: 非法的月份 %d\n", month);
        return -1;
    }
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (day < 1 || day > daytab[leap][month]) {
        printf("day_of_year: 非法的日号 %d\n", day);
        return -1;
    }
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: 把一年中的第几天转换成月、日；出错时置 -1 */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap, total;

    if (year < 1 || yearday < 1) {
        printf("month_day: 非法的天数 %d\n", yearday);
        *pmonth = -1;
        *pday = -1;
        return;
    }
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    total = 0;
    for (i = 1; i <= 12; i++)
        total += daytab[leap][i];
    if (yearday > total) {
        printf("month_day: 非法的天数 %d\n", yearday);
        *pmonth = -1;
        *pday = -1;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

int main(void)
{
    int m, d;

    printf("day_of_year(2024, 3, 1) = %d\n", day_of_year(2024, 3, 1));
    printf("day_of_year(2024, 13, 1) = %d\n", day_of_year(2024, 13, 1));
    month_day(2024, 61, &m, &d);
    printf("month_day(2024, 61) = %d月%d日\n", m, d);
    month_day(2024, 366, &m, &d);
    printf("month_day(2024, 366) = %d月%d日\n", m, d);
    month_day(2024, 367, &m, &d);
    printf("month_day(2024, 367) = %d月%d日\n", m, d);
    return 0;
}
