/*
  @pintia psid=2102248980422123520 pid=2102248980443095041 compiler=GCC
  ProblemSet: 1.分支结构(if / switch)
  Title: 求该月天数
  https://pintia.cn/problem-sets/2102248980422123520/exam/problems/type/7?problemSetProblemId=2102248980443095041
*/
// @pintia code=start
#include <stdio.h>

int main()
{
    int y, m;
    int d = 28;
    scanf("%d %d", &y, &m);
    if (!(m>=1&&m<=12))
    {
        printf("ERROR");
        return 0;
    }
    
    // 31天：1 3 5 7 8 10 12
    // 30天：4 6 9 11
    // 29天：闰2
    // 28天：平2
    switch (m) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        d = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        d = 30;
        break;
    }
    if ((y % 400 == 0 || y % 4 == 0 && !(y % 100 == 0)) && m == 2) {
        d = 29;
    }
    printf("%d", d);
    return 0;
}
// @pintia code=end