//全對
#include<iostream>
#include<set>

int main()
{
  std::string input;
  std::set<char> data;
  std::getline(std::cin, input);
  int max = 0, buf = 0;
  for(int i = 0;i < input.length();i++)
  {
    data.clear();
    buf = 0;
    for(int j = i;j < input.length();j++)
    {
      if(data.find(input[j]) == data.end())
      {
        data.insert(input[j]);
        buf++;
      }
      else
      {
        if(buf > max)
          max = buf;
        break;
      }
    }
    if(buf > max)
      max = buf;
  }

  std::cout << max << std::endl;
}
