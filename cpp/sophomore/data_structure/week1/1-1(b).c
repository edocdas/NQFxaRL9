#include <stdio.h>
#include <stdlib.h>
void allocArray(int ***p, int row, int col)
{
  int **set_array = (int **)malloc(row * sizeof(int *));
  int *inside_array = (int *)malloc(row*col * sizeof(int));

  for(int i = 0;i < row;i++)
  {
    set_array[i] = inside_array + i * col;
  }

  *p = set_array;
  //p = &set_array;
  /*我不能把在函式內的物件位址傳回去，不過可以把這指標指向的物件傳回*/
}

int main()
{
  int **array, *a;
  int j, k;
  allocArray(&array, 5, 10);
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
    {
      printf("%p ", &(array[j][k]));
      //printf("%d ", array[j][k]);
    }
}