#include<iostream>
  class go{
  public:
    void input();
    void operation();
    void check(int , int);
    void print();

  private:
    char table[9][9];
    bool black_touch = false, white_touch = false;
    int black = 0, white = 0, buf_counter = 0;
  };

void go::input(){
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

void go::operation(){
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
        buf_counter = 0;
        black_touch = false;
        white_touch = false;
        check(i, j);
        if(black_touch && white_touch)
          continue;
        else
        {
          if(black_touch)
            black += buf_counter;
          else if(white_touch)
            white += buf_counter;
        }
      }
    }
  }
}

void go::check(int i, int j){
  if(i < 0 || i >= 9 || j < 0 || j >= 9 || table[i][j] == '*')
    return;

  if(table[i][j] == '.')
  {
    buf_counter++;
    table[i][j] = '*';
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
  std::cout << "Black " << black << " White " << white << std::endl;
}

int main(){
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
