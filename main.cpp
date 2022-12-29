#include<iostream>
#include<map>

auto change(std::map<std::string, int>&map)
{  
  return map.begin()++->second = 99999;
}

int main()
{
  std::map<std::string, int> map;
  map.insert(std::pair<std::string,int>("he",1));
  map.insert(std::pair<std::string,int>("hell",3));
  map.insert(std::pair<std::string,int>("ho",123));

  auto iter = change(map);
  std::cout << "get iter:" << iter->first << " " << iter->second;
  for(auto it:map)
    std::cout << it.first << " " << it.second << std::endl;
}