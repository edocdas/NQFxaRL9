#include<iostream>
int main(){
  int a = 0;
  while(std::cin >> a)
  {
    int total = a, empty_bottle = a;
    while(empty_bottle >= 3)
    {
      total += empty_bottle / 3;
      empty_bottle = (empty_bottle/3)+(empty_bottle%3);
    }
    if(empty_bottle == 2)
      total += 1;
    std::cout << total << '\n';
  }
}
