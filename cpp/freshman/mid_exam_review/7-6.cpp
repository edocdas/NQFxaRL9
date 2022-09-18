#include<iostream>
#include<cstring>

int main()
{
  int test_case = 0;
  std::cin >> test_case;

  for(int i = 1;i <= test_case;i++)
  {
    int day = 0, parties = 0;
    std::cin >> day >> parties;
    int strike_data[day];
    std::memset(strike_data, 0, sizeof(strike_data));

    for(int j = 1;j <= parties;j++)
    {
      int buf_day = 0;
      std::cin >> buf_day;
      for(int i = 1 ;i <= day;i++)
      {
        if(i % buf_day == 0)
          strike_data[i-1] = 1;
      }
    }

    int result = 0;
    for(int i = 1 ;i <= day;i++)
    {
      if((i+1) % 7 == 0 || i % 7 == 0 || strike_data[i-1] == 0)
        continue;
      else
        result++;
    }

    std::cout << result << std::endl;
  }
}
