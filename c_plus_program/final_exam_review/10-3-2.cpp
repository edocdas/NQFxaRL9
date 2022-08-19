#include<iostream>

#define For(i,a,b) for(int i = a;i <= b;i++)
bool table[2][100][100];

void Operation(int index)
{
  int data_count = 0;
  char buf_a, buf_b;
  std::cin >> data_count;
  for(int i = 1;i <= data_count;i++)
  {
    std::cin >> buf_a >> buf_b;
    //打錯了
    table[index][buf_a][buf_b] = table[index][buf_b][buf_a] = true;
  }

  For(i,'A','Z')
    For(j,'A','Z')
      For(k,'A','Z')
        table[index][j][k] = table[index][j][k] || (table[index][j][i] && table[index][i][k]);
        //淺在問題
}

bool compare()
{
  For(i,'A','Z')
    For(j,'A','Z')
      if(table[0][i][j] != table[1][i][j])
        return false;

  return true;
}

int main()
{
  int test_case = 0;
  std::cin >> test_case;
  for(int i = 1;i <= test_case;i++)
  {
    //忘記初始化
    For(i,'A','Z')
      For(j,'A','Z')
        table[0][i][j] = table[1][i][j] = false;


    Operation(0);
    Operation(1);
    if(compare())
    {
      std::cout << "YES\n";
    }
    else
      std::cout << "NO\n";

    std::cout << "\n";
    //記得每次都要換行
  }
}
