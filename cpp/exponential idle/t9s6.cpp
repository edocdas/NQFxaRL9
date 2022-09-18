#include<iostream>
#include<cmath>
#define _USE_MATH_DEFINES

int main()
{
  int end = 500;
  int target_a = 0, target_b = 0;
  double min = 10;

  for(int a = 1;a <= end;a++)
  {
    for(int b = 1;b <= end;b++)
      if(pow(a,1/exp(1))-pow(b,1/M_PI) > 0 && pow(a,1/exp(1))-pow(b,1/M_PI) < min)
      {
        target_a = a;
        target_b = b;
        min = pow(a,1/exp(1))-pow(b,1/M_PI);

        std::cout << "a:" << target_a << " b:" << target_b << " min:" << min << std::endl;
      }
  }

  std::cout << "The smallest is " << min << std::endl;
  std::cout << "at a:" << target_a << " b:" << target_b << std::endl; 
}
