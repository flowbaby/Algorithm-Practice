#include <stdio.h>

int main()
{
  double fahr, celsius;
  int lower, upper, step;

  lower = -100;
  upper = 200;
  step = 20;

  printf("摄氏度与华氏度对照表：\n");

  celsius = lower;

  for (; celsius <= upper;)
  {
    fahr = celsius * 9 / 5 + 32;
    printf("%6.0lf\t%6.1lf\n", celsius, fahr);
    celsius += step;
  }

  return 0;
}