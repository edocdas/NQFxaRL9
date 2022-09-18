//https://www.cplusplus.com/reference/string/string/substr/
//https://www.cplusplus.com/reference/string/string/find/
//https://blog.gtwang.org/programming/c-memory-functions-malloc-free/
//有整數加小數的情況嗎？
//0的問題 ex.123.11-123.11 = 0 or 0.00

#include<iostream>
#include<string>
#include<cstdlib>
#include<cstdio>

class BigNumber{
public:
  BigNumber()=default;
  BigNumber(std::string input_str)
  {
    if(input_str[0] == '-')
    {
      positive = false; //是負數
      number = input_str.substr(1);
    }
    else
      number = input_str;
  }
  void print()
  {
    if(positive)
      std::cout << number << '\n';
    else
      std::cout << "-" << number << '\n';
  }

  bool a_bigger_num(std::string a, std::string b) const //絕對值比較大小
  {
    if(a.length() > b.length()) //看哪個比較大
      return true;
    else if(b.length() > a.length())
      return false;
    else
    {
      for(int i = 0;i < a.length();i++) //兩個長度一樣
      {
        if(a[i] > b[i])
          return true;
        else if(a[i] < b[i])
          return false;
      }
    }
    return false;
  }
  BigNumber add_condiction(BigNumber a, BigNumber b) const
  {
    BigNumber result;
    if(a.positive == true && b.positive == true) //兩者皆為正數
      result.number = add(a.number, b.number);
    else if(a.positive == false && b.positive == false) //兩者皆為負數
    {
      result.number = add(a.number, b.number);
      result.positive = false;
      //一正一負，負數比較大（最後面的條件是避免兩個數相同，但一正一負）
    }else if((a_bigger_num(a.number, b.number) && a.positive == false)||
      (!a_bigger_num(a.number, b.number) && b.positive == false && a.number != b.number))  //一正一負，但負數比較大
    {
      result.number = minus(a.number, b.number);
      result.positive = false;
    }else //一正一負，正數比較大
    {
      result.number = minus(a.number, b.number);
      result.positive = true;
    }

    int not_zero = 0; //把前面的0清除掉
    //只剩一個0，就停止
    while(result.number[not_zero] == '0' && not_zero + 1 != result.number.length())
      not_zero++;
    result.number = result.number.substr(not_zero); //取得從非0開始的字串

    return result;
  }

  BigNumber minus_condiction(BigNumber a, BigNumber b) const
  {
    BigNumber result;
    if(a.positive == true && b.positive == true) //兩者皆為正數
    {
      result.number = minus(a.number, b.number); //預設為a-b
      if(!a_bigger_num(a.number,b.number) && a.number != b.number) //a比b小，為負數
          result.positive = false;
    }
    else if(a.positive == true && b.positive == false) //前正後負
    {
      result.number = add(a.number, b.number);
      result.positive = true;
    }else if(a.positive == false && b.positive == true) //前負後正
    {
      result.number = add(a.number, b.number);
      result.positive = false;
    }else if(a_bigger_num(a.number, b.number) && a.positive == false && b.positive == false)
    //皆負，但前方絕對數值比較大
    {
      result.number = minus(a.number, b.number);
      result.positive = false;
    }else if(!(a_bigger_num(a.number, b.number) && a.positive == false && b.positive == false))
    //皆負，但後方絕對數值比較大
    {
      result.number = minus(a.number, b.number);
      result.positive = true;
    }

    int not_zero = 0; //把前面的0清除掉
    while(result.number[not_zero] == '0' && not_zero + 1 != result.number.length())
      not_zero++;
    result.number = result.number.substr(not_zero);

    return result;
  }

  //小數後面不夠位數，需要補零
  void fill_zero_character(BigNumber *input, int difference) const
  {
    int old_length = input->number.length(); //舊的長度
    input->number.resize(input->number.length()+difference); //string 增加大小
    for(int z = old_length;z < input->number.length();z++) //填充0
    {
      input->number[z] = '0';
    }
  }

  void remove_dot(BigNumber *input) const
  {
    int without_dot_len = 0;
    for(int i = 0;i < input->number.length();i++)
    {
      if(input->number[i]!='.')
      {
        input->number[without_dot_len] = input->number[i];
        without_dot_len++;
      }
    }
    input->number.resize(input->number.length()-1); //減少一個長度
  }

  std::string put_dot_and_zero(std::string input, int dot_to_last) const
  {
    if(input.length() <= dot_to_last)//需要補0與.號
    {
      int index = 0, old_length = input.length();
      input.resize(dot_to_last+2);
      for(index = 0;old_length-1-index >= 0;index++)
      {
        input[input.length()-1-index] = input[old_length-1-index];
      }
      input[0] = '0';
      input[1] = '.';
      for(;input.length()-1-index >= 2;index++)
      {
        input[input.length()-1-index] = '0';
      }
      return input;
    }else //只需要補.號
    {
      input.resize(input.length()+1);
      int index = 0;
      for(index = 0;index < dot_to_last;index++)
      {
        input[input.length()-1-index] = input[input.length()-2-index];
      }
      input[input.length()-1-index] = '.';
      return input;
    }
  }

  //相加與相減都預設為正整數運作，如果為負數的情況，會在多載裡面討論
  std::string add(std::string a, std::string b) const
  {

    bool a_bigger = false, b_bigger = false;
    a.length() >= b.length() ? a_bigger = true : b_bigger = true; //判定哪個位數比較大

    std::string final_string;
    a_bigger ? final_string.resize(a.length()+1) : final_string.resize(b.length()+1);
    //多預設一個位數，以免進位
    int a_length = a.length(), b_length = b.length();
    int string_len = final_string.length();
    final_string = std::string(string_len, '0'); //結果預設為0


    for(;string_len > 0;string_len--,a_length--,b_length--)
    {
      int a_current = 0, b_current = 0;//避免某一方已經先沒數字
      a_length > 0 ? a_current = a[a_length-1] - '0' : a_current = 0;
      b_length > 0 ? b_current = b[b_length-1] - '0' : b_current = 0;

      //std::cout << "string_len:" << string_len << " a_current:"
      //<< a_current << " b_current:" << b_current << '\n';

      //需要考量到增加的數字，要包含現在這個位數的進位
      int digit = (final_string[string_len-1] - '0') + a_current + b_current;
      if(digit >= 10)
      {
        final_string[string_len-2] += 1; //進一位(最多也只會進一位)
        final_string[string_len-1] = (digit % 10) + '0'; //取餘數
      }
      else
        final_string[string_len-1] = digit + '0';

      //for(int index = 0;index < final_string.length();index++)
      //  std::cout << final_string[index] << '\n';
    }
    return final_string;
  }

  std::string minus(std::string a, std::string b) const
  {
    std::string final_string;
    bool a_bigger = false, b_bigger = false;
    a_bigger_num(a,b) ? a_bigger = true : b_bigger = true; //比較字串大小


    a_bigger ? final_string.resize(a.length()) : final_string.resize(b.length());
    int a_length = a.length(), b_length = b.length();
    int string_len = final_string.length();
    final_string = std::string(string_len, '0');

    for(;string_len > 0;string_len--,a_length--,b_length--)
    {
      int a_current = 0, b_current = 0, digit = 0;//避免某一方已經先沒數字
      a_length > 0 ? a_current = a[a_length-1] - '0' : a_current = 0;
      b_length > 0 ? b_current = b[b_length-1] - '0' : b_current = 0;

      //std::cout << "string_len:" << string_len << " a_current:"
      //<< a_current << " b_current:" << b_current << '\n';

      if(a_bigger) //a比b大
      {
          digit = a_current - b_current;
          if(digit < 0) //不夠減
          {
            a[a_length-2] -= 1; //借一位
            final_string[string_len-1] = (digit + 10) + '0';
          }
          else
            final_string[string_len-1] = digit + '0'; //夠減
      }
      else //b比a大
      {
        digit = b_current - a_current;
        if(digit < 0)
        {
          b[b_length-2] -= 1;
          final_string[string_len-1] = (digit + 10) + '0';
        }
        else
          final_string[string_len-1] = digit + '0';
      }
      //for(int index = 0;index < final_string.length();index++)
      //  std::cout << final_string[index] << '\n';
    }
    return final_string;
  }
  BigNumber& operator+ (const BigNumber& b_const)const
  {
    BigNumber a = *this, b = b_const; //變成可更改的 BigNumber
    BigNumber *result = new BigNumber; //結果 BigNumber;
    if(this->number.find(".") == -1) //兩者為整數
    {
      *result = add_condiction(a, b);
    }else
    {
      int dot_to_last = 0;
      int a_dot_index = a.number.find("."), b_dot_index = b.number.find(".");
      int a_dot_to_end = a.number.length()-1-a_dot_index;
      int b_dot_to_end = b.number.length()-1-b_dot_index; //ex. 1.1 & 1.111

      if(a_dot_to_end > b_dot_to_end) //b需要填充0
      {
        dot_to_last = a_dot_to_end;
        fill_zero_character(&b, a_dot_to_end-b_dot_to_end);
      }else
      {
        dot_to_last = b_dot_to_end;
        fill_zero_character(&a, b_dot_to_end-a_dot_to_end);
      }
      remove_dot(&a); //把.號移除掉
      remove_dot(&b); //把.號移除掉

      *result = add_condiction(a, b);
      //std::cout << "add complete" <<result->number << std::endl;
      if(result->number[0] == '0' && result->number.length() == 1)
        return *result;
      else
        result->number = put_dot_and_zero(result->number, dot_to_last); //把.號放回去
    }
    return *result;
  }
  BigNumber& operator- (const BigNumber b_const)const
  {
    BigNumber a = *this, b = b_const; //變成可更改的 BigNumber
    BigNumber *result = new BigNumber; //結果 BigNumber;
    if(this->number.find(".") == -1) //兩者為整數
    {
      *result = minus_condiction(a, b);
    }else
    {
      int dot_to_last = 0;
      int a_dot_index = a.number.find("."), b_dot_index = b.number.find(".");
      int a_dot_to_end = a.number.length()-1-a_dot_index;
      int b_dot_to_end = b.number.length()-1-b_dot_index;

      if(a_dot_to_end > b_dot_to_end) //b需要填充0
      {
        dot_to_last = a_dot_to_end;
        fill_zero_character(&b, a_dot_to_end-b_dot_to_end);
      }else
      {
        dot_to_last = b_dot_to_end;
        fill_zero_character(&a, b_dot_to_end-a_dot_to_end);
      }
      remove_dot(&a); //把.號移除掉
      remove_dot(&b); //把.號移除掉

      *result = minus_condiction(a, b);
      //std::cout << "add complete" <<result->number << std::endl;
      if(result->number[0] == '0' && result->number.length() == 1)
        return *result;
      else
        result->number = put_dot_and_zero(result->number, dot_to_last); //把.號放回去
    }
    return *result;
  }
private:
  std::string number;
  bool positive = true; //預設為正數
};

int main(){
  //freopen("input.txt","r", stdin);
  //freopen("output.txt","w", stdout);

  std::string input_fir, input_sec;
  std::cin >> input_fir >> input_sec;

  BigNumber a(input_fir), b(input_sec);
  BigNumber c = a+b, d = a-b;
  c.print();
  d.print();


  //std::cout << input_fir << "+" << input_sec << "=" << result << '\n';


  return 0;
}
