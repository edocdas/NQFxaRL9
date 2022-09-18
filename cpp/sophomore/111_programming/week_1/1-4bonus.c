#include<stdio.h>

int main()
{
  int a = 85, b = 91, c = 99;
  printf("%d %d %d\n", a, b, c);
  printf("float:%f\n", (float)(a+b+c)/3);
  printf("double:%lf\n\n", (double)(a+b+c)/3);
  printf("float to 10:%.10f\n", (float)(a+b+c)/3);
  printf("double to 10:%.10lf\n", (double)(a+b+c)/3);
  return 0;
}
