#include <iostream>
class F
{
public:
  F():a(0), b(0){}
  F(int input_a, int input_b): a(input_a), b(input_b){}
  int S(int end_num);
  int G(int begin_num, int end_num);
  friend F& operator +(const F& first, const F& second);
  friend F& operator -(const F& first, const F& second);
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

F& operator +(const F& first, const F& second){
  F* ptr = new F;
  ptr->a = first.a + second.a;
  ptr->b = first.b + second.b;
  return *ptr;
}

F& operator -(const F& first, const F& second){
  F* ptr = new F;
  ptr->a = first.a - second.a;
  ptr->b = first.b - second.b;
  return *ptr;
}

int main() {
  int a, b, j, c, d;
  std::cin>>a>>b>>c>>d;
  F f(a, b), f2(c, d);
  for(j = 0;j < 10;j ++)
  {
    int x, y;
    std::cin>>x>>y;
    std::cout<<(f + f2).S(x)<<std::endl;
    std::cout<<(f - f2).G(x, y)<<std::endl;
  }
  return 0;
}
