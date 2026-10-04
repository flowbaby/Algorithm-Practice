/*
 * 答案7-03 扩展minprintf
 *
 * 提示：minprintf 用 <stdarg.h> 的可变参数机制逐个处理格式串中的转换说明。扩展时注意类型提升规则：整数参数一律以 int 取（%d/%i/%o/%u/%x/%X/%c），浮点一律以 double 取（%f/%e/%g），字符串以 char* 取，%% 输出字面百分号。对不认识的转换符原样输出即可。
 */
#include <stdarg.h>
#include <stdio.h>

/* minprintf: 支持 d,i,o,u,x,X,c,s,f,e,g,%% 的最小 printf */
void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    unsigned int uval;
    double dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':
        case 'i':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'o':
            ival = va_arg(ap, int);
            printf("%o", ival);
            break;
        case 'u':
            uval = va_arg(ap, unsigned int);
            printf("%u", uval);
            break;
        case 'x':
        case 'X':
            uval = va_arg(ap, unsigned int);
            printf(*p == 'x' ? "%x" : "%X", uval);
            break;
        case 'c':
            ival = va_arg(ap, int);
            putchar(ival);
            break;
        case 's':
            sval = va_arg(ap, char *);
            fputs(sval, stdout);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 'e':
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        case 'g':
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;
        case '%':
            putchar('%');
            break;
        default:
            putchar('%');
            putchar(*p);
            break;
        }
    }
    va_end(ap);
}

int main(void)
{
    char s[] = "world";
    minprintf("int=%d hex=%x char=%c str=%s f=%f e=%e g=%g %%\n",
              42, 255, 'A', s, 3.14159, 3.14159, 3.14159);
    return 0;
}
