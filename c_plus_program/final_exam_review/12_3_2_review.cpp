#include<iostream>
#include<map>
#include<set>

int target = 0;
std::multiset<int> input_data;
std::multimap<int, std::multiset<int>> result_data;

void recur(std::multiset<int>::iterator data_it, int count
  , std::multiset<int> cur_set)
{
  data_it++;
  for(auto beg = data_it;beg != input_data.end();beg++)
  {
    std::multiset<int> set_buf = cur_set;
    set_buf.insert(*beg);
    int sum = 0;
    for(auto it:set_buf)
      sum += it;

    //忘記make_pair
    if(sum == target)
      result_data.insert(std::make_pair(count, set_buf));

    //recur 寫錯
    recur(beg, count+1, set_buf);
  }
}

int main()
{
  int inp = 0, buf = 0;
  std::cin >> inp >> target;
  for(int i = 0;i < inp;i++)
  {
    std::cin >> buf;
    input_data.insert(buf);
  }

  for(auto beg = input_data.begin();beg != input_data.end();beg++)
  {
    std::multiset<int> set_buf;
    set_buf.insert(*beg);
    if(*beg == target)
      result_data.insert(std::make_pair(1, set_buf));

    recur(beg, 2, set_buf);
  }

  bool swap = true;
  while(swap)
  {
    swap = false;
    int counter = 1;
    for(auto it = result_data.begin();it != result_data.end();it++)
    {
      for(auto it2 = it;it2 != result_data.end();it2++)
      {
        if(it->first == counter && it2->first == counter && it->second > it2->second)
        {
          it->second.swap(it2->second);
          swap = true;
        }
      }
    }
    counter++;
  }

  for(auto it : result_data)
  {
    for(auto it2 : it.second)
      std::cout << it2 << " ";
    std::cout << '\n';
  }
}
