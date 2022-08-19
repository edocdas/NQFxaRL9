#include<iostream>
#include<string>
#include<set>

int main()
{
  std::string input;
  std::getline(std::cin, input);
  std::set<char> data;

  int max = 0, buf = 0;
  for(int i = 0;i < input.length();i++)
  {
    buf = 0;
    data.clear();
    for(int j = i ;j < input.length();j++)
    {
      if(data.find(input[j]) == data.end())
      {
        data.insert(input[j]);
        buf++;
      }
      else
      {
        break;
      }
    }
    if(buf > max)
      max = buf;
  }
  std::cout << max << std::endl;
}
