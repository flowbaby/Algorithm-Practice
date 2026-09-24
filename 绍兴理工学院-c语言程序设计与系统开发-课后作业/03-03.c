// 某城市出租车收费标准如下：起步里程为3公里，起步费10元；超过起步里程后10公里内，每公里2元；超过10公里，10公里以上的部分加收50%的空驶补贴费，每公里3元；营运过程中，因道路拥堵及乘客要求临时停车的，按每5分钟2元计收（不足5分钟则不收费）。运价计费尾数四舍五入，保留到元。

// 编写程序，输入行驶公里与等待时间，计算并输出乘客应支付的车费。
#include <math.h>
#include <stdio.h>

int main()
{
    double km;
    int time;
    scanf("%lf %d", &km, &time);
    int sum = time / 5 * 2;

    if (km > 10) {
        sum = (int)round(sum + (km - 10) * 3 + 7 * 2 + 10);
    } else if (km > 3) {
        sum = (int)round(sum + (km - 3) * 2 + 10);
    } else {
        sum = (int)round(sum + 10);
    }
    printf("%d", sum);
    return 0;
}