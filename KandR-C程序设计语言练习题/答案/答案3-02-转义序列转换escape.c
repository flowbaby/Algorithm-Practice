/*
 * 答案3-02 转义序列转换escape
 *
 * 提示：escape 用 switch 把换行、制表等不可见字符转换为由两个字符组成的可见转义
 * 序列；unescape 反向操作，遇到 '\\' 时读取下一个字符决定实际字符。
 * 注意两个方向都要正确复制字符串结尾的 '\0'，且 unescape 对孤立的 '\\' 要能安全处理。
 */
#include <stdio.h>

void escape(char s[], char t[])
{
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
        case '\n':
            s[j++] = '\\';
            s[j++] = 'n';
            break;
        case '\t':
            s[j++] = '\\';
            s[j++] = 't';
            break;
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i, j;

    for (i = j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
        case '\\':
            switch (t[++i]) {
            case 'n':
                s[j++] = '\n';
                break;
            case 't':
                s[j++] = '\t';
                break;
            default:        /* '\' 后面不是 n/t：按字面输出 */
                s[j++] = '\\';
                s[j++] = t[i];
                break;
            }
            break;
        default:
            s[j++] = t[i];
            break;
        }
    }
    s[j] = '\0';
}

int main(void)
{
    char t[] = "Hello\tWorld\nGood bye.";
    char s[100];

    escape(s, t);
    printf("escape:   %s\n", s);

    unescape(s, s);
    printf("unescape: %s\n", s);

    return 0;
}
