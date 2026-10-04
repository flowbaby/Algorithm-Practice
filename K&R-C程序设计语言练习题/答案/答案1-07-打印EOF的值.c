/*
 * 答案1-07 打印EOF的值
 *
 * 提示：EOF 是在 <stdio.h> 中定义的宏，在大多数系统中值为 -1。直接用 printf("%d", EOF) 即可打印；也可以在 getchar() 返回 EOF 时打印该返回值确认一致。
 */
#include <stdio.h>

int main()
{
    printf("EOF is %d\n", EOF);
    return 0;
}
