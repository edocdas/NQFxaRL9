#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<cmath>

class F{
public:
  F() = default;
  F(double input_a, double input_r): a(input_a), r(input_r){}
  double at(int x){ return a*pow(r,x);}
  double* S()
  {
    if(r > -1 && r < 1)
    {
      double *ptr = new double;
      *ptr = a/(1-r);
      return ptr;
    }
    else
      return nullptr;
  }


private:
  double a, r;
};

int main()
{
	int j, k;
	double a, r;
	std::cin>>a>>r;
	F f(a, r);
	for(k = 0;k < 3;k ++)
		printf("%.2lf\n", f.at(k));
	double *s = f.S();
    if(s == NULL)
      printf("NULL\n");
  else
	printf("%.2lf\n", *s);
}
