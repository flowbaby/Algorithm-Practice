/*
 * 答案4-13 递归版reverse
 *
 * 提示：用两个 static 下标 i、j。i 先向前走到字符串末尾（递归前进），回溯时
 * 把字符按倒序写回 s[j++]；最深层把 i、j 重置为 0，这样返回各层时用 s[0]
 * 是否为空来判断是否该重置，从而支持多次调用。整体是“先取字符，后写回”的
 * 经典递归反转。
 */
#include <stdio.h>

void reverse(char s[])
{
    static int i = 0, j = 0;
    char c;

    if (s[i]) {
        c = s[i++];
        reverse(s);
        s[j++] = c;
    }
    if (s[i] == '\0')
        i = j = 0;                    /* 一次反转完成，复位供下次使用 */
}

int main(void)
{
    char s1[] = "hello";
    char s2[] = "abc";
    char s3[] = "x";

    reverse(s1);
    printf("%s\n", s1);

    reverse(s2);
    printf("%s\n", s2);

    reverse(s3);
    printf("%s\n", s3);

    return 0;
}
