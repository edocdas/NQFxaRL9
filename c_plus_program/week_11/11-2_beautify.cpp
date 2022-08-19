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

    int b_dex = 0, e_dex = 0;
    while(true)
    {
      if(data[i-1].find_first_not_of(data[i-1][b_dex], b_dex) != std::string::npos)
      {
        e_dex = data[i-1].find_first_not_of(data[i-1][b_dex], b_dex);
        data[i] += std::to_string(e_dex-b_dex) + data[i-1][b_dex];
        b_dex = e_dex;
      }
      else
        break;
    }
    data[i] += std::to_string(data[i-1].size() - b_dex) + data[i-1][b_dex];
  }

  int input = 0;
  while(std::cin >> input)
    std::cout << data[input-1] << std::endl;
}
