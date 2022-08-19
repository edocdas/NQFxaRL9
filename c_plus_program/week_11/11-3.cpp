#include<iostream>
#include<string>
#include<map>
#include<cstring>

int main()
{
  int data_count = 0;
  std::map<char, char> data[100];
  std::string input;
  while(std::getline(std::cin, input), input[0]!= '#')
  {

    if(input[0] != 'e')
    {
      for(int i = 0;i <= 16;i += 4) //map幫你排好順序
        data[data_count].insert(std::make_pair(input[i] ,input[i+2]));
      data_count++;
      continue;
    }
    else
    {

      int result_list[data_count]; //結果陣列
      memset(result_list, -1, sizeof(result_list));

      for(int j = 0;j < data_count;j++) //目前的城市
      {
        for(int k = 0;k < data_count;k++) //比較的城市
        {
          if(j == k)
            continue;

          std::map<char,char> buf_j = data[j], buf_k = data[k];
          auto comp1 = buf_j.begin(), comp2 = buf_k.begin();

          for(int l = 0;l < 5;l++,comp1++,comp2++)
          {
            if((comp1)->second == (comp2)->second)
              continue;
            else
            {
              result_list[j] += 1;
            }
          }
        }
      }

      int least = result_list[0], least_index = 0;
      for(int a = 0;a < data_count;a++)
      {
        if(result_list[a] < least)
        {
          least = result_list[a];
          least_index = a;
        }
      }
      std::cout << least_index+1 << std::endl;
    }

    for(int g = 0;g < 100;g++)
      data[g].clear();
    data_count = 0;
  }
}
