#include<iostream>

int main()
{
  int digits = 0, game = 1;
  while(std::cin >> digits, digits != 0)
  {
    std::cout << "Game " << game++ << ":\n";
    int ans[digits];
    for(int i = 0;i < digits;i++)
      std::cin >> ans[i];

    while(true)
    {
      int a = 0, b = 0;
      int test[digits];
      int ans_list[10] = {0}, test_list[10] = {0};

      for(int i = 0;i < digits;i++)
        std::cin >> test[i];

      if(test[0] == 0)
        break;

      for(int i = 0;i < digits;i++)
      {
        if(ans[i] == test[i])
          a++;

        ans_list[ans[i]]++;
        test_list[test[i]]++;
      }

      for(int i = 0;i < 10;i++)
      {
        ans_list[i] > test_list[i] ? b += test_list[i] : b += ans_list[i];
      }

      std::cout << "(" << a << "," << b-a << ")\n";
    }
  }
}
