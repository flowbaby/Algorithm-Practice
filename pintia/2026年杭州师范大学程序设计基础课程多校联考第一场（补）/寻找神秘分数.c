/*
  @pintia psid=2115441217247838208 pid=2115441217461764104 compiler=GCC
  ProblemSet: 2026年杭州师范大学程序设计基础课程多校联考第一场（补）
  Title: 寻找神秘分数
  https://pintia.cn/problem-sets/2115441217247838208/exam/problems/type/7?problemSetProblemId=2115441217461764104
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    long long nume_llast = 0;
    long long deno_llast = 1;
    long long nume_last = 1;
    long long deno_last = 1;
    long long nume, deno;
    long long index = 3;
    long long find_index = -1;
    long long P, Q;
    scanf("%lld %lld", &P, &Q);
    if (P == 0 && Q == 1) {
        printf("1");
        return 0;
    } else if (P == 1 && Q == 1) {
        printf("2");
        return 0;
    }

    do {
        nume = nume_llast + nume_last;
        deno = deno_llast + deno_last;
        nume_llast = nume_last;
        deno_llast = deno_last;
        nume_last = nume;
        deno_last = deno;
        if (P == nume && Q == deno) {
            find_index = index;
            break;
        }
        index++;
    } while (P > nume && Q > deno);
    printf("%lld", find_index);
    return 0;
}
// @pintia code=end