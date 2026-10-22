/*
  @pintia psid=2112024660870381568 pid=2112024661063319553 compiler=GCC
  ProblemSet: 2022-2023 学年秋学期程序设计基础联考第一场
  Title: 曼哈顿距离与切比雪夫距离
  https://pintia.cn/problem-sets/2112024660870381568/exam/problems/type/7?problemSetProblemId=2112024661063319553
*/
// @pintia code=start
#include <stdio.h>
#include <stdlib.h>
int main(){
    int x1,y1,x2,y2;
    scanf("%d %d",&x1,&y1);
    scanf("%d %d",&x2,&y2);
    int re1 = abs(x2-x1);
    int re2 = abs(y2-y1);
    int max =re1;
    if(re2>max) max =re2;
    printf("%d %d",re1+re2,max);
    return 0;
}

// @pintia code=end