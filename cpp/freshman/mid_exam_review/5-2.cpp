#include<iostream>

class go
{
public:
  void input();
  void operation();
  void check(int, int);
  void print();
private:
  char table[9][9];
  bool white_touch = false, black_touch = false;
  int white = 0, black = 0, counter = 0;
};

void go::input()
{
  for(int i = 0;i < 9;i++)
  {
    for(int j = 0;j < 9;j++)
    {
      char buf;
      std::cin >> buf;
      table[i][j] = buf;
    }
  }
}

void go::operation()
{
  for(int i = 0;i < 9;i++)
  {
    for(int j = 0;j < 9;j++)
    {
      if(table[i][j] == 'O')
        white++;
      else if(table[i][j] == 'X')
        black++;
      else if(table[i][j] == '.')
      {
        white_touch = false;
        black_touch = false;
        counter = 0;

        check(i,j);
        if(white_touch && black_touch)
          continue;
        else if(white_touch)
          white += counter;
        else if(black_touch)
          black += counter;
      }
    }
  }
}

void go::check(int i, int j)
{
  if(i < 0 || i > 8 || j < 0 || j > 8 || table[i][j] == '*')
    return;

  if(table[i][j] == '.')
  {
    counter++;
    table[i][j] = '*'; //忘記加這行
  }
  else if(table[i][j] == 'O')
  {
    white_touch = true;
    return;
  }
  else if(table[i][j] == 'X')
  {
    black_touch = true;
    return;
  }
  check(i-1,j);
  check(i+1,j);
  check(i,j-1);
  check(i,j+1);
}

void go::print()
{
  std::cout << "Black "<< black << " White " << white << std::endl;
}

int main()
{
  int test_case = 0;
  std::cin >> test_case;
  for(int i = 1;i <= test_case;i++)
  {
    go a;
    a.input();
    a.operation();
    a.print();
  }
}
