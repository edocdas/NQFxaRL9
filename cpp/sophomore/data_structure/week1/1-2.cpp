#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class Memory
{
public:
  static T **allocArray(int row, int col)
  {
    T **set_array = (T **)malloc(row * sizeof(T *));
    for(int i = 0;i < row;i++)
    {
        set_array[i] = (T *)malloc(col * sizeof(T));
    }
    return set_array;
  }
};

int main()
{
  int **array;
  array = Memory<int>::allocArray(5, 10);
  int j, k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      cout<<array[j][k]<<" ";
}