/*
 * 答案4-02 atof支持科学计数法
 *
 * 提示：在基本 atof 的基础上，解析完整数与小数部分后检查是否有 e/E；若有，读取
 * 可选符号与指数，算出 10 的相应幂，再与已得到的数值相乘（负指数则相除）。
 * 注意先把数值部分完整解析出来，最后再整体施加指数，避免精度损失。
 */
#include <stdio.h>
#include <ctype.h>

double atof(char s[])
{
    double val, power, scale;
    int i, sign, esign, exp;

    for (i = 0; isspace(s[i]); i++)      /* 跳过空白 */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)  /* 整数部分 */
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {   /* 小数部分 */
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E') {    /* 科学计数法指数部分 */
        i++;
        esign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (exp = 0; isdigit(s[i]); i++)
            exp = 10 * exp + (s[i] - '0');
        for (scale = 1.0; exp > 0; exp--)
            scale *= 10.0;
        if (esign < 0)
            return sign * val / power / scale;
        else
            return sign * val / power * scale;
    }

    return sign * val / power;
}

int main(void)
{
    printf("%g\n", atof("123.45e-6"));
    printf("%g\n", atof("123.45E+2"));
    printf("%g\n", atof("   -3.5e3"));
    printf("%g\n", atof("0.5"));
    printf("%g\n", atof("2e2"));

    return 0;
}
