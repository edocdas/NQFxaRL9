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
-1 -1 -2 -2 -3 -3 -4 -4 -5 -5
*/

#include<iostream>
#include<cstdio>
#include<map>
#include<set>

class subset{
public:
  void input();
  void operation();
  void sort_data();
  void print();
private:
  void recur(const std::multiset<int>, const int, const std::multiset<int>::iterator);
  int input_num = 0, target = 0; //有幾筆資料 & 目標
  std::multiset<int> data; //資料
  std::multimap<int, std::multiset<int>> result_data; //最終結果
};

void subset::input()
{
  int buf = 0;
  std::cin >> input_num >> target;
  for(int i = 1;i <= input_num;i++)
  {
    std::cin >> buf;
    data.insert(buf);
  }
}

void subset::operation()
{
  for(auto it = data.begin();it != data.end();it++)
  {
    std::multiset<int> cur_set = {*it};

    if(*it == target) //第一個元素就滿足
      result_data.insert(std::make_pair(1, cur_set));

    recur(cur_set, 2, it);
  }
}

void subset::recur(const std::multiset<int> cur_set,const int count,
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

void subset::sort_data()
{
  int counter = 1;

  for(auto it = result_data.begin();it != result_data.end();)
  {
    if(it->first == counter)
    {
      auto begin = it, next = begin;
      for(;begin != result_data.end() && begin->first == counter;begin++)
      {
        for(;next != result_data.end() && next->first == counter;next++)
        {
          if(next->second < begin->second)
          {
            std::multiset<int> buf = next->second;
            next->second = begin->second;
            begin->second = buf;
          }
        }
      }
      it = begin; //換成下一個數量的子集
    }
    counter++; //遞增數量
  }
}

void subset::print()
{
  if(result_data.empty()) //如果是空的狀況
    return ;

  //int total_case = 0; //測試全部的狀況
  std::string str_output;

  for(auto it = result_data.begin();it != result_data.end();it++)
  {
    for(auto set_ele : it->second)
    {
      str_output += (std::to_string(set_ele) + " ");
    }
    //str_output.erase(str_output.end()-1); //把最後的空白刪掉
    str_output += "\n";

    //total_case++;
  }
  //str_output.erase(str_output.end()-1); //把最後的換行刪掉
  std::cout << str_output;
  //std::cout << "total_case:" << total_case << std::endl;
}

int main()
{
  subset a;
  a.input();
  a.operation();
  a.sort_data();
  a.print();
}
