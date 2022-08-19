#include <iostream>
class F
{
public:
  F():a(0), b(0){}
  F(int input_a, int input_b): a(input_a), b(input_b){}
  int S(int end_num);
  int G(int begin_num, int end_num);
private:
  int a;
  int b;
};

int F::S(int end_num){
  int sum = 0;
  for(int i = 0; i <= end_num;i++)
  {
    sum += (a*i+b);
  }
  return sum;
}

int F::G(int begin_num, int end_num){
  int sum = 0;
  for(int i = begin_num; i <= end_num;i++)
  {
    sum += (a*i+b);
  }
  return sum;
}

int main() {
  int a, b, j;
  std::cin>>a>>b;
  F f(a, b);
  for(j = 0;j < 10;j ++)
  {
    int x, y;
    std::cin>>x>>y;
    std::cout<<f.S(x)<<std::endl;
    std::cout<<f.G(x, y)<<std::endl;
  }
  return 0;
}
