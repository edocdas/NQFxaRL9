//https://blog.csdn.net/weixin_42584156/article/details/122150778

#include<cmath>
#include<iostream>

double banker_rounding(const double input)
{
  long long int trun_num = trunc((fabs(input) - fabs(trunc(input)))*100000);
  double bonus = 0;
  
  //此數為負數的情況
  bool isNegative = false;
  if(input < 0)
  {
    isNegative = true;
  }
  //如果剛好進位到1，就會結束
  while(trun_num > 100)
  {
    //大於5，直接進位
    if(trun_num % 10 > 5)
      trun_num += 10;
    //等於5，不過前一位為奇數
    else if(trun_num % 10 == 5 && (trun_num / 10) % 10 % 2 == 1)
      trun_num += 5;
    
    trun_num /= 10;
  }

  if(isNegative)
    return trunc(input) - (trun_num / 100.0);
  else
    return trunc(input) + (trun_num / 100.0);
}

int main()
{
  std::cout << banker_rounding();
}