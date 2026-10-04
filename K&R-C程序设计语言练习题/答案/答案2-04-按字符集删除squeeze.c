/*
 * 答案2-04 按字符集删除squeeze
 *
 * 提示：外层循环遍历 s1 的每个字符，内层循环在 s2 中查找该字符是否出现。
 * 若在 s2 中找不到，则把该字符保留到 s1 前面的位置；最后补上字符串
 * 结束符 '\0'。
 */
#include <stdio.h>

void squeeze(char s1[], char s2[])
{
    int i, j, k;

    for (i = j = 0; s1[i] != '\0'; ++i) {
        for (k = 0; s2[k] != '\0' && s2[k] != s1[i]; ++k)
            ;
        if (s2[k] == '\0')
            s1[j++] = s1[i];
    }
    s1[j] = '\0';
}

int main(void)
{
    char s[] = "hello world";
    squeeze(s, "lo");
    printf("%s\n", s);
    return 0;
}
