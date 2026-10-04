/*
 * 答案4-01 最右出现位置strindex
 *
 * 提示：对 s 中每个可能的起始位置 i，用内层循环与 t 逐字符比较；每当完整匹配成功
 * （t 的所有字符都相等），就把位置 i 记录下来并继续向后扫描，这样最后保留的
 * 自然是最右一次出现的位置。若从未匹配则返回 -1。
 */
#include <stdio.h>

int strindex(char s[], char t[])
{
    int i, j, k, pos;

    pos = -1;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            pos = i;
    }
    return pos;
}

int main(void)
{
    char s[] = "the cat and the dog and the bird";
    char t1[] = "the";
    char t2[] = "dog";
    char t3[] = "xyz";
    char t4[] = "and";

    printf("strindex(\"%s\", \"%s\") = %d\n", s, t1, strindex(s, t1));
    printf("strindex(\"%s\", \"%s\") = %d\n", s, t2, strindex(s, t2));
    printf("strindex(\"%s\", \"%s\") = %d\n", s, t3, strindex(s, t3));
    printf("strindex(\"%s\", \"%s\") = %d\n", s, t4, strindex(s, t4));

    return 0;
}
