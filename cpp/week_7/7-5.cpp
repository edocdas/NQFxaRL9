#include<iostream>
#include<cmath>

int main(){
  int a = 0, b = 0;
  while(std::cin >> a >> b, a != 0 && b != 0)
  {
    
    int result = 0;
    for(int i = a;i <= b;i++)
    {
      double test = sqrt(i);

      if(test-int(test) == 0)
        result++;
    }
    std::cout << result << '\n';
  }
  return 0;
}
