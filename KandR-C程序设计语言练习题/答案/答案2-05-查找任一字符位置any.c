/*
 * 答案2-05 查找任一字符位置any
 *
 * 提示：遍历 s1 中的每个字符，在 s2 中查找是否出现；一旦找到即返回
 * 当前下标 i。若整个 s1 遍历完毕仍未找到，则返回 -1。
 */
#include <stdio.h>

int any(char s1[], char s2[])
{
    int i, j;

    for (i = 0; s1[i] != '\0'; ++i)
        for (j = 0; s2[j] != '\0'; ++j)
            if (s1[i] == s2[j])
                return i;
    return -1;
}

int main(void)
{
    printf("any(\"hello\", \"lo\") = %d\n", any("hello", "lo"));
    printf("any(\"abc\", \"xyz\") = %d\n", any("abc", "xyz"));
    return 0;
}
