/*
 * 答案7-04 私有版scanf
 *
 * 提示：与 minprintf 对称地使用 va_list，但可变参数是"指针"，必须按 int*/unsigned*/double*/char* 取出后写入目标。空白处理上，格式串中的空白与输入中的空白互相匹配，由本函数用 getchar/ungetc 自行跳过；%c 例外，不跳过前导空白。实际的字符到数值的转换可以委托给标准 scanf 完成（用 %lf 对应 double*），失败时停止并返回已成功赋值的个数。
 */
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

/* minscanf: 支持 d,i,o,x,u,c,s,f,e,g 的最小 scanf，返回成功赋值的项数 */
int minscanf(char *fmt, ...)
{
    va_list ap;
    char *p;
    int *ivalp;
    unsigned int *uvalp;
    double *dvalp;
    char *sval;
    int c, count = 0;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (isspace(*p)) {
            while (isspace(c = getchar()))
                ;
            if (c != EOF)
                ungetc(c, stdin);
            continue;
        }
        if (*p != '%') {          /* 字面字符必须匹配 */
            c = getchar();
            if (c != *p) {
                if (c != EOF)
                    ungetc(c, stdin);
                break;
            }
            continue;
        }
        switch (*++p) {
        case 'd':
        case 'i':
            ivalp = va_arg(ap, int *);
            while (isspace(c = getchar()))
                ;
            if (c == EOF)
                goto done;
            ungetc(c, stdin);
            if (scanf(*p == 'd' ? "%d" : "%i", ivalp) != 1)
                goto done;
            count++;
            break;
        case 'o':
        case 'x':
        case 'u':
            uvalp = va_arg(ap, unsigned int *);
            while (isspace(c = getchar()))
                ;
            if (c == EOF)
                goto done;
            ungetc(c, stdin);
            if (scanf(*p == 'o' ? "%o" : *p == 'x' ? "%x" : "%u", uvalp) != 1)
                goto done;
            count++;
            break;
        case 'c':                 /* %c 不跳过空白，读单个字符 */
            ivalp = va_arg(ap, int *);
            if ((c = getchar()) == EOF)
                goto done;
            *ivalp = c;
            count++;
            break;
        case 's':
            sval = va_arg(ap, char *);
            while (isspace(c = getchar()))
                ;
            if (c == EOF)
                goto done;
            do {
                *sval++ = c;
            } while ((c = getchar()) != EOF && !isspace(c));
            *sval = '\0';
            if (c != EOF)
                ungetc(c, stdin);
            count++;
            break;
        case 'f':
        case 'e':
        case 'g':
            dvalp = va_arg(ap, double *);
            while (isspace(c = getchar()))
                ;
            if (c == EOF)
                goto done;
            ungetc(c, stdin);
            if (scanf("%lf", dvalp) != 1)   /* %f 在 scanf 中对应 double* */
                goto done;
            count++;
            break;
        default:
            break;
        }
    }
done:
    va_end(ap);
    return count;
}

int main(void)
{
    int i;
    double d;
    char word[100];

    printf("请输入 整数 浮点数 字符串（如：42 3.14 hello）：\n");
    if (minscanf("%d %f %s", &i, &d, word) == 3)
        printf("读到: i=%d, d=%g, word=%s\n", i, d, word);
    else
        printf("输入格式不完整\n");
    return 0;
}
