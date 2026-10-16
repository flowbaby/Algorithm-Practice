// 某系统设有密码，允许用户最多进行三次尝试，如果规定次数内密码输入正确则提示“登录成功”，否则给出相应提示。

// 如：密码正确
//         密码错误，还剩下2次机会
//         密码错误，还剩下1次机会
//         密码错误，没有机会

// 对数组使用sizeof可得数组单元的长度×数值长度
//`fgets`会把回车`\n`读到 buf 里面
#include <stdio.h>
#include <string.h>

int main()
{
    char* pwd = "2abc11*$@! _23";
    char buf[20];
    for (int i = 3; i > 0;) {
        fgets(buf, sizeof(buf), stdin);
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }

        i--;
        if (strcmp(pwd, buf) == 0) {
            printf("密码正确\n");
            break;
        } else if (i == 0) {
            printf("密码错误，没有机会\n");
        } else {
            printf("密码错误，还剩下%d次机会\n", i);
        }
    }

    return 0;
}