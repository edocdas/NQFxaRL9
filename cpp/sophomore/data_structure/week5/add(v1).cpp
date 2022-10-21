#include<iostream>

void add(std::string a_int, std::string a_dec, std::string b_int, std::string b_dec)
{
  //補足整數的0
  while(a_int.length() > b_int.length())
    b_int = "0" + b_int;
  while(a_int.length() < b_int.length())
    a_int = "0" + a_int;
  
  //補足小數的0
  while(a_dec.length() > b_dec.length())
    b_dec = b_dec + "0";
  while(a_dec.length() < b_dec.length())
    a_dec = a_dec + "0";

  //整數計算
  int result_int[10000] = {0}, carry = 0;
  for(int i = a_int.length()-1, res_i = 0;i >= 0;i--, res_i++)
  {
    result_int[res_i] = (a_int[i] - '0') + (b_int[i] - '0') + carry;
    carry = result_int[res_i] / 10;
    result_int[res_i] %= 10;
  }
  //剛好進位
  if(carry == 1)
    result_int[a_int.length()] = 1;

  
  //小數計算
  int result_dec[10000] = {0}, bonus = 0;
  for(int i = a_dec.length()-1, res_i = 0;i >= 0;i--, res_i++)
  {
    result_dec[res_i] = (a_dec[i] - '0') + (b_dec[i] - '0') + bonus;
    bonus = result_dec[res_i] / 10;
    result_dec[res_i] %= 10;
  }
  //剛好進位(ex. 9.999 + 0.001)
  if(bonus == 1)
  {
    result_int[0] += 1;
    
    //處理連續進位的情況
    int index = 0;
    while(result_int[index] == 10)
    {
      result_int[index] %= 10;
      result_int[index+1] += 1;
      index++;
    }
  }

  std::string res_str_int, res_str_dec;
  //得出最終整數字串
  for(int i = 0;i < a_int.length()+1;i++)
  {
    //如果沒有額外進一位
    if(result_int[i] == 0 && i == a_int.length())
      continue;
    
    res_str_int = char(result_int[i] + '0') + res_str_int;
  }

  //得出最終小數字串
  for(int i = 0;i < a_dec.length();i++)
  {
    res_str_dec = char(result_dec[i] + '0') + res_str_dec;
  }

  std::cout << "integer:" << res_str_int << "\n";
  std::cout << "decimal:" << res_str_dec << "\n";
}