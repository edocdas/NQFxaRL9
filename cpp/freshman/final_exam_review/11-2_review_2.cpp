#include<iostream>
#include<string>

int main()
{
  std::string data[30];
  for(int i = 0;i < 30;i++)
  {
    if(i == 0)
    {
      data[0] = '1';
      continue;
    }

    int beg = 0, end = 0;
    while(data[i-1].find_first_not_of(data[i-1][beg], beg) != std::string::npos)
    {
      end = data[i-1].find_first_not_of(data[i-1][beg], beg);
      data[i] += std::to_string(end-beg) + data[i-1][beg];
      beg = end;
    }
    data[i] += std::to_string(data[i-1].size()-beg) + data[i-1][beg];
  }

  int num;
  while(std::cin >> num)
    std::cout << data[num-1] << std::endl;
}
