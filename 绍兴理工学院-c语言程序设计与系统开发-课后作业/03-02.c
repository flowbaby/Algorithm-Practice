// 输入学生人数n，再输入n个学生的成绩，统计五分制成绩的分布。百分制成绩到五分制成绩的转换规则为：大于或等于90分为A,小于90分且大于或等于80分为B，小于80分且大于或等于70分为C，小于70分且大于或等于60分为D，小于60分为E。（switch结构实现）
#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    double input;
    int A, B, C, D, E;
    A = B = C = D = E = 0;

    for (int i = 0; i < n; i++) {
        scanf("%lf", &input);
        switch ((int)input / 10) {
        case 10:
        case 9:
            A++;
            break;
        case 8:
            B++;
            break;
        case 7:
            C++;
            break;
        case 6:
            D++;
            break;
        default:
            E++;
            break;
        }
    }

    printf("A:%d\n", A);
    printf("B:%d\n", B);
    printf("C:%d\n", C);
    printf("D:%d\n", D);
    printf("E:%d\n", E);
    return 0;
}