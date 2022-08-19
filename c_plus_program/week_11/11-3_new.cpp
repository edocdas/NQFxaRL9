#include<iostream>
#include<string>
#include<climits>

void compare(char (&data)[110][5], int count)
{
  int tar_index = 0, min = INT_MAX;
  for(int a = 0;a < count;a++)
  {
    int min_buf = 0;
    for(int b = 0;b < count;b++)
    {
      for(int c = 0;c < 5;c++)
      {
        if(data[a][c] != data[b][c])
          min_buf++;
      }
    }
    if(min_buf < min)
    {
      min = min_buf;
      tar_index = a;
    }
  }

  std::cout << tar_index+1 << std::endl;
}

int main()
{
  int count = 0;
  char data[110][5];
  std::string buf;
  while(std::getline(std::cin, buf), buf != "#")
  {
    if(buf[0] == 'e')
    {
      compare(data, count);
      count = 0;
    }
    else
    {
      for(int i = 0;i < 5;i++)
      {
        char ch = buf[i*4];
        int put = 0;

        if(ch == 'r')
          put = 0;
        else if(ch == 'o')
          put = 1;
        else if(ch == 'y')
          put = 2;
        else if(ch == 'g')
          put = 3;
        else if(ch == 'b')
          put = 4;

        data[count][put] = buf[i*4 + 2];
      }
      count++;
    }
  }
}
