/*

1
11
21
1211
111221
*/
#include<iostream>
#include<string>

int main()
{
  std::string data[30];
  for(int i = 0;i < 30;i++)
  {
    if(i == 0)
    {
      data[0] = "1";
      continue;
    }

    int buf_counter = 1;
    char current = data[i-1][0]; //要比較的字元（先放第一個）
    for(int j = 1;j < data[i-1].length();j++)
    {
      if(current == data[i-1][j])
        buf_counter++;
      else
      {
        data[i] += std::to_string(buf_counter) + current;
        buf_counter = 1;
        current = data[i-1][j];
      }
    }
    data[i] += std::to_string(buf_counter) + current;
  }

  int input = 0;
  while(std::cin >> input)
    std::cout << data[input-1] << std::endl;
}
