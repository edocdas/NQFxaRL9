#include<iostream>
#include<iomanip>

int main(){
  double a = 0;
  while(std::cin >> a)
    std::cout << std::fixed << std::setprecision(3) << a << std::endl;
  return 0;
}
