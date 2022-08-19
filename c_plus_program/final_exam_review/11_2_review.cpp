#include<iostream>
#include<string>

int main()
{
  std::string data[30];
  for(int i = 0;i < 30;i++)
  {
    if(i == 0)
    {
      //打錯了
      data[0] = "1";
      continue;
    }

    int begin = 0, end = 0;
    while(data[i-1].find_first_not_of(data[i-1][begin], begin) != std::string::npos)
    {
      end = data[i-1].find_first_not_of(data[i-1][begin], begin);
      data[i] += std::to_string(end-begin) + data[i-1][begin];
      begin = end;
    }

    data[i] += std::to_string(data[i-1].size()-begin) + data[i-1][begin];
  }

  int num = 0;
  while(std::cin >> num)
  {
    std::cout << data[num-1] << std::endl;
  }
}
