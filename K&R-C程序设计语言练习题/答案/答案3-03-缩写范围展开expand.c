/*
 * 答案3-03 缩写范围展开expand
 *
 * 提示：扫描 s1 中的 '-'：若其前一个字符是字母或数字、后一个字符是与前者同类的
 * 字符且不小于前者，就按升序把两者之间的连续字符依次写入 s2；否则 '-' 原样复制。
 * 这样 a-b-c、a-z0-9 能正确展开，-a-z 的开头 '-'、结尾的 '-' 以及 z-a 这类
 * 倒序记号都按字面处理。
 */
#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[])
{
    int i, j, c;

    i = j = 0;
    while ((c = s1[i++]) != '\0') {          /* 从 s1 取一个字符 */
        if (s1[i] == '-' && s1[i + 1] >= c && isalnum(c) && isalnum(s1[i + 1])) {
            i++;                              /* 跳过 '-' */
            while (c < s1[i])
                s2[j++] = c++;
        } else
            s2[j++] = c;                      /* 原样复制 */
    }
    s2[j] = '\0';
}

int main(void)
{
    char s1[] = "a-z 0-9 a-b-c a-z0-9 -a-z z-a -A-Z-";
    char s2[500];

    expand(s1, s2);
    printf("%s\n%s\n", s1, s2);

    return 0;
}
