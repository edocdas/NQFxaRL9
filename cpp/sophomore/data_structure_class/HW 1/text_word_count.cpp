#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
#include<map>
#include<cctype>

int main()
{
  std::ifstream file;
  std::map<std::string, int> data;

  file.open("./input.txt");
  if(file.fail())
    std::cout << "Read fail\n" << std::endl;

  while(!file.eof())
  {
    std::string input;
    file >> input;

    std::string::iterator iter_begin = input.begin(), iter_end;

    //std::cout << "string:" << input << std::endl;
    while(iter_begin != input.end() && !isalpha(*iter_begin))
    {
      //std::cout << "forward:" << *iter_begin << std::endl;
      input.erase(iter_begin);
    }

    iter_end = input.end()-1;
    while(iter_end != input.begin() && input != "" && !isalpha(*iter_end))
    {
      //std::cout << "backward:" << *iter_end << std::endl;
      input.erase(iter_end);
      iter_end--;
    }

    if(input == "")
      continue;
    if(data.find(input) != data.end())
      data[input] += 1;
    else
      data[input] = 1;
  }

  for(auto it = data.begin();it != data.end();it++)
  {
    std::cout << it->first << std::setw(15 - it->first.length());

    for(int i = 0;i < it->second;i++)
    {
      std::cout << "*";
    }
    std::cout << it->second << std::endl;
  }
}
