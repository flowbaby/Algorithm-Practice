/*
 * 答案5-09 指针版日期函数
 *
 * 提示：用 char *p 指向 daytab[leap] 这一行，通过 p[month] 或
 * 移动指针访问各月天数，完全不用下标。day_of_year 中让 p 指向当月
 * 之前的月份依次累加；month_day 中同样用指针遍历减去各月天数。
 * 错误检查保留练习 5-08 的版本。
 */
#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: 根据年、月、日计算一年中的第几天（指针版） */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    char *p;

    if (year < 1 || month < 1 || month > 12) {
        printf("day_of_year: 非法的月份 %d\n", month);
        return -1;
    }
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (day < 1 || day > *(*(daytab + leap) + month)) {
        printf("day_of_year: 非法的日号 %d\n", day);
        return -1;
    }
    p = *(daytab + leap);               /* p 指向该年 1 月之前的表头 */
    for (i = 1; i < month; i++)
        day += *++p;                    /* 依次加上前面各月的天数 */
    return day;
}

/* month_day: 把一年中的第几天转换成月、日（指针版） */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap, total;
    char *p;

    if (year < 1 || yearday < 1) {
        printf("month_day: 非法的天数 %d\n", yearday);
        *pmonth = -1;
        *pday = -1;
        return;
    }
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    total = 0;
    p = *(daytab + leap);
    for (i = 1; i <= 12; i++)
        total += p[i];
    if (yearday > total) {
        printf("month_day: 非法的天数 %d\n", yearday);
        *pmonth = -1;
        *pday = -1;
        return;
    }
    p = *(daytab + leap);
    for (i = 1; yearday > *++p; i++)
        yearday -= *p;
    *pmonth = i;
    *pday = yearday;
}

int main(void)
{
    int m, d;

    printf("day_of_year(2023, 12, 31) = %d\n", day_of_year(2023, 12, 31));
    printf("day_of_year(2024, 12, 31) = %d\n", day_of_year(2024, 12, 31));
    month_day(2024, 60, &m, &d);
    printf("month_day(2024, 60) = %d月%d日\n", m, d);
    month_day(2023, 365, &m, &d);
    printf("month_day(2023, 365) = %d月%d日\n", m, d);
    return 0;
}
