/*
5 3
1 2 -1 4 -2

7 1
1 2 3 4 5 6 7

8 2
-3 -1 1 1 2 3 0 0

10 0
0 0 0 0 0 0 0 0 0 0

7 -2
-3 -2 -1 -1 0 0 0

10 -10
-1 -2 -3 -4 -5 -1 -2 -3 -4 -5
*/

#include<iostream>
#include<cstdio>
#include<map>
#include<set>

int input_num = 0, target = 0; //有幾筆資料 & 目標
std::multiset<int> data; //資料
std::multimap<int, std::multiset<int>> result_data; //最終結果



void recur(const std::multiset<int> cur_set,const int count,
                  const std::multiset<int>::iterator data_iter)
{
  auto recur_iter = data_iter;
  for(recur_iter++;recur_iter != data.end();recur_iter++)
  {
    int recur_sum = 0;
    std::multiset<int>recur_set = cur_set;
    recur_set.insert(*recur_iter);

    for(auto recur_set_it:recur_set)
      recur_sum += recur_set_it;

    if(recur_sum == target) //目前的set等於target
    {
      result_data.insert(std::make_pair(count, recur_set));
    }

    recur(recur_set, count+1, recur_iter);
  }
}

int main()
{
  int buf = 0;
  std::cin >> input_num >> target;
  for(int i = 1;i <= input_num;i++)
  {
    std::cin >> buf;
    data.insert(buf);
  }

  for(auto it = data.begin();it != data.end();it++)
  {
    std::multiset<int> cur_set = {*it};

    if(*it == target) //第一個元素就滿足
      result_data.insert(std::make_pair(1, cur_set));

    recur(cur_set, 2, it);
  }




  for(auto it = result_data.begin();it != result_data.end();it++)
  {
    bool swa;
    int counter = it->first;
    while(true)
    {
      swa = false;

      auto begin = it, next = begin;
      for(;begin != result_data.end() && begin->first == counter;begin++)
      {
        for(;next != result_data.end() && next->first == counter;next++)
        {
          /*std::cout << "first set:" << begin->first << std::endl;
          for(auto out : begin->second)
            std::cout << out << " ";
          std::cout << "\n";

          std::cout << "second set:" << next->first << std::endl;
          for(auto out : next->second)
            std::cout << out << " ";
          std::cout << "\n";*/

          if(next->second < begin->second)
          {
            //std::cout << "Swap\n";
            next->second.swap(begin->second);
            swa = true;
          }
        }
      }

      if(!swa)
      {
          break;
      }
    }
  }


  for(auto it = result_data.begin();it != result_data.end();it++)
  {
    for(auto set_ele : it->second)
    {
      std::cout << std::to_string(set_ele) + " ";
    }
    std::cout << "\n";
  }
}
