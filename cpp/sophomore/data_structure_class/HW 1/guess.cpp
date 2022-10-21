#include<iostream>
#include<cstdlib>
#include<cstring>

bool program_guess(const int try_time, const int upper_limit)
{
  int upper = upper_limit, lower = 1;

  for(int i = 1;i <= try_time;i++)
  {
    int rand_num = (rand() % (upper-lower+1)) + lower;
    char ch[100];

    std::cout << "\nRound " << i << " :" << rand_num << std::endl;
    std::cout << "Is the number correct?\n(type Below or Within or Above)\n";
    std::cin >> ch;

    if(strcmp(ch, "Below") == 0)
    {
      std::cout << "Read your response, below\n";
      upper = rand_num - 1;
    }
    else if(strcmp(ch, "Above") == 0)
    {
      std::cout << "Read your response, above\n";
      lower = rand_num + 1; 
    }
    else
    {
      return 1;
    }
  }
  return 0;
}

int main()
{
  int try_time = 0, upper_limit = 0;
  
  std::cout << "Please type your try_time, upper_limit, I'll trying to guess.\n";
  std::cin >> try_time >> upper_limit;

  srand(time(NULL));
  if(program_guess(try_time, upper_limit))
    std::cout << "I find the number!\n";
  else
    std::cout << "I can't find the number!\n";
}