#include<iostream>
#include<set>
#include<cmath>
#include<bitset>

int main()
{
  int input_num = 0, target = 0, buf = 0, data_count = 0;
  int input_data[32];
  std::cin >> input_num >> target;
  for(int i = 1;i <= input_num;i++)
  {
    std::cin >> buf;
    input_data[data_count] = buf;
    data_count++;
  }

  for(int i = 0;i < data_count;i++)
  {
    for(int j = i;j < data_count;j++)
    {
      if(input_data[i] > input_data[j])
      {
        buf = input_data[i];
        input_data[i] = input_data[j];
        input_data[j] = buf;
      }
    }
  }


  std::multiset<std::multiset<int>> result_data[32]; //以index當作有多少的元素
  for(int i = 0;i < pow(2,input_num);i++)
  {
    std::bitset<32> binary(i); //預定可以處理最多32個
    int sum = 0, oper_count = 0;

    for(int j = 0;j < input_num;j++)
    {
      if(binary[j] == 1)
      {
        sum += input_data[j];
        oper_count++;
      }
    }

    if(sum == target)
    {
      std::multiset<int> buf_set;
      for(int j = 0;j < input_num;j++)
      {
        if(binary[j] == 1)
          buf_set.insert(input_data[j]);
      }
      result_data[oper_count].insert(buf_set);
    }
  }

  std::string str_output;
  for(auto it : result_data)
  {
    for(auto it2 : it)
    {

      for(auto iter = it2.begin();iter != it2.end();iter++)
      {
        str_output += std::to_string(*iter) + " ";
      }
      str_output.erase(str_output.end()-1);
      str_output += "\n";
    }
  }
  str_output.erase(str_output.end()-1);
  std::cout << str_output;
}
