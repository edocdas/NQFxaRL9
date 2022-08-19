#include<iostream>
#include<map>
#include<set>

std::multiset<int> input_data;
std::multimap<int,std::multiset<int>> result_data;
int target = 0;

void recur(std::multiset<int>::iterator it, int count, std::multiset<int> cur_set)
{
  it++;
  for(auto it2 = it;it2 != input_data.end();it2++)
  {
    std::multiset<int> re_set = cur_set;
    re_set.insert(*it2);

    int sum = 0;
    for(auto it3: re_set)
      sum += it3;
    if(sum == target)
      result_data.insert(std::make_pair(count, re_set));

    recur(it2, count+1, re_set);
  }
}

int main()
{
  int count = 0, buf = 0;
  std::cin >> count >> target;

  for(int i = 0;i < count;i++)
  {
    std::cin >> buf;
    input_data.insert(buf);
  }

  for(auto it = input_data.begin();it != input_data.end();it++)
  {
    std::multiset<int> cur_set = {*it};
    if(*it == target)
      result_data.insert(std::make_pair(1, cur_set));

    recur(it, 2, cur_set);
  }

  int counter = 1;
  bool swap = false;
  while(true)
  {
    for(auto it = result_data.begin();it != result_data.end();it++)
    {
      for(auto it2 = it;it2 != result_data.end();it2++)
      {
        //這邊忘記加 counter 的條件
        if(it->first == counter && it2->first == counter && it->second > it2->second)
          it->second.swap(it2->second);
      }
    }

    counter++;
    if(!swap)
      break;
  }

  for(auto it: result_data)
  {
    for(auto it2: it.second)
      std::cout << it2 << " ";
    std::cout << "\n";
  }
}
