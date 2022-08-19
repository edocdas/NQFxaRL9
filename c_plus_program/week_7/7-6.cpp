#include<iostream>
#include <cstring>

int main(){
  int test_case = 0;
  std::cin >> test_case;

  for(int i = 0;i < test_case;i++)
  {
    int days = 0, parties = 0;
    int stop_days = 0;
    std::cin >> days >> parties;
    int data[days];
    memset(data, 0, sizeof(data));
    for(int j = 0;j < parties;j++)
    {
      int hartal_day = 0;
      std::cin >> hartal_day;
      for(int k = 1;k <= days;k++)
      {
        if(k % hartal_day == 0)
          data[k-1] = 1;
      }
    }
    bool First_friday = true, First_saturdays = true;
    for(int j = 0;j < days;j++)
    {
      if(j == 5 && First_friday)
      {
        First_friday = false;
        continue;
      }else if(j == 6 && First_saturdays)
      {
        First_saturdays = false;
        continue;
      }else if((j+2) % 7 == 0 || (j+1) % 7 == 0)
        continue;
      else if(data[j] == 1)
        stop_days++;
    }
    std::cout << stop_days << '\n';
  }

  return 0;
}
