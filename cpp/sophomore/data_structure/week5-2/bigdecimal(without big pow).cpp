#include<iostream>
#include<cstring>
#include<string>

#define SIZE 1000

class BigDecimal
{
  public:
  BigDecimal() = default;
  BigDecimal(std::string int_arr, std::string dec_arr)
  {
    this->ch_int_arr = int_arr;
    this->ch_dec_arr = dec_arr;

  }
  BigDecimal(const BigDecimal &input)
  {
    this->ch_int_arr = input.ch_int_arr;
    this->ch_dec_arr = input.ch_dec_arr;
    this->positive = input.positive;
  }


  static void set_substr(std::string *input, std::string *in_int, std::string *in_dec)
  {
    //找點號
    size_t dot = input->find(".");

    //整數情況
    if(dot == std::string::npos)
    {
      *in_int = *input;
      *in_dec = "0";
    }
    else
    //小數情況
    {
      *in_int = input->substr(0, dot);
      *in_dec = input->substr(dot+1);
    }
  }

  bool bigger(const BigDecimal *a, const BigDecimal *b) const
  {
    //檢查整數
    if(a->ch_int_arr.length() > b->ch_int_arr.length())
      return true;
    
    if(a->ch_int_arr.length() < b->ch_int_arr.length())
      return false;

    for(int i = 0;i <= a->ch_int_arr.length() || i << b->ch_int_arr.length();i++)
    {
      if(a->ch_int_arr[i] > b->ch_int_arr[i])
        return true;
      if(a->ch_int_arr[i] < b->ch_int_arr[i])
        return false;
    }

    //檢查小數
    if(a->ch_dec_arr.length() > b->ch_dec_arr.length())
      return true;
    
    if(a->ch_dec_arr.length() < b->ch_dec_arr.length())
      return false;

    for(int i = 0;i <= a->ch_dec_arr.length() || i << b->ch_dec_arr.length();i++)
    {
      if(a->ch_dec_arr[i] > b->ch_dec_arr[i])
        return true;
      if(a->ch_dec_arr[i] < b->ch_dec_arr[i])
        return false;
    }

    //兩者相同
    return true;
  }

  bool bigger_integer(const std::string *a_int, const std::string *b_int)
  {
    if(a_int->length() > b_int->length())
      return true;
    else if(a_int->length() < b_int->length())
      return false;
    else
    {
      for(int i = 0;i < a_int->length();i++)
      {
        if(a_int[i] > b_int[i])
          return true;
        else if(a_int[i] < b_int[i])
          return false;
      }

      //兩者相同
      return true;
    }
  }

  bool equal(std::string *a_int, std::string *b_int)
  {
    if(a_int->length() > b_int->length())
      return false;
    else if(a_int->length() < b_int->length())
      return false;
    else
    {
      for(int i = 0;i < a_int->length();i++)
      {
        if(a_int[i] > b_int[i])
          return false;
        else if(a_int[i] < b_int[i])
          return false;
      }

      //兩者相同
      return true;
    }
  }


  static void check_9(char *ch, int iter, int *bonus)
  {
    if(ch[iter] == '9')
    {
      //std::cout << "equal nine:" << iter << std::endl; 
      ch[iter] = '0';
      check_9(ch, iter-1, bonus);
    }
    else if(ch[iter] < '9' && ch[iter] >= '0')
    {
      //std::cout << "smaller than nine:" << iter << std::endl; 
      ch[iter] += 1;
    }
    else if(ch[iter] == '.')
    {
      //std::cout << "find dot:" << iter << std::endl; 
      (*bonus) = (*bonus) + 1;
    }
  }

  //想法，把小數轉成整數後計算
  static void banker_rounding(std::string *a, std::string *b)
  {
    char i_arr[a->length()+1], d_arr[b->length()+1];
    strcpy(i_arr, a->c_str());
    strcpy(d_arr, b->c_str());

    int bonus = 0;
    char *dot_place = 0;
    char ch[SIZE];

    strcpy(ch, i_arr);
    strcpy(ch+strlen(ch), ".");
    strcpy(ch+strlen(ch), d_arr);
    dot_place = strchr(ch, '.');
    

    for(int i = strlen(ch)-1; ch[i-2] != '.' && ch[i-1] != '.';i--)
    {
      if(ch[i] - '0' > 5 || (ch[i] - '0' == 5 && (ch[i-1] - '0') % 2 == 1) 
      || (i != strlen(ch)-1 && ch[i] - '0' == 5 && (ch[i-1] - '0') % 2 == 0 && ch[i+1] != '0'))
      {
        ch[i] = '0';
        check_9(ch, i-1, &bonus);
      }
    }
    *(dot_place + 3) = '\0';


    int index = -1;
    dot_place[index] += bonus;
    while(dot_place[index] == '0' + 10)
    {
      dot_place[index] = '0';

      //剛好全部都進位了，ex. 999.988 -> 1000.00
      if(dot_place+index == ch)
      {
        char buf[SIZE];
        strcpy(buf, "1");
        strcpy(buf+strlen(buf), ch);
        strcpy(ch, buf);
        break;
      }

      dot_place[index-1] += 1;
      index--;
    }

    dot_place = strchr(ch, '.');
    strncpy(i_arr, ch, dot_place-ch);
    strcpy(d_arr, dot_place+1);


    *a = i_arr;
    *b = d_arr;
  }

  BigDecimal* operator+(const BigDecimal *input) const
  {
    BigDecimal *output;
    //正加正
    if(this->positive && input->positive)
    {
      //std::cout << "Positive + Posivite\n";
      output = add(this->ch_int_arr, this->ch_dec_arr, input->ch_int_arr, input->ch_dec_arr);
      output->positive = true;
    }
    //負加負
    else if(!this->positive && !input->positive)
    {
      //std::cout << "Negative + Negative\n";
      output = add(this->ch_int_arr, this->ch_dec_arr, input->ch_int_arr, input->ch_dec_arr);
      output->positive = false;
    }
    //正加負
    else if(this->positive && !input->positive)
    {
      //std::cout << "Positive + Negative\n";
      if(bigger(this, input))
      {
        output = sub(this->ch_int_arr, this->ch_dec_arr, input->ch_int_arr, input->ch_dec_arr);
        output->positive = true;
      }
      else
      {
        output = sub(input->ch_int_arr, input->ch_dec_arr, this->ch_int_arr, this->ch_dec_arr);
        output->positive = false;
      }
    }
    //負加正
    else if(!this->positive && input->positive)
    {
      //std::cout << "Negative + Positive\n";
      if(bigger(this, input))
      {
        output = sub(this->ch_int_arr, this->ch_dec_arr, input->ch_int_arr, input->ch_dec_arr);;
        output->positive = false;
      }
      else
      {
        output = sub(input->ch_int_arr, input->ch_dec_arr, this->ch_int_arr, this->ch_dec_arr);
        output->positive = true;
      }
    }

    

    //使用banker's rounding
    //banker_rounding(output->ch_int_arr, output->ch_dec_arr);

    return output;
  }


  BigDecimal* operator-(const BigDecimal *input) const
  {
    BigDecimal *output;
    //正減負
    if(this->positive && !input->positive)
    {
      output = add(this->ch_int_arr, this->ch_dec_arr, input->ch_int_arr, input->ch_dec_arr);
      output->positive = true;
    }
    //負減正
    else if(!this->positive && input->positive)
    {
      output = add(this->ch_int_arr, this->ch_dec_arr, input->ch_int_arr, input->ch_dec_arr);
      output->positive = false;
    }
    //正減正
    else if(this->positive && input->positive)
    {
      if(bigger(this, input))
      {
        output = sub(this->ch_int_arr, this->ch_dec_arr, input->ch_int_arr, input->ch_dec_arr);
        output->positive = true;
      }
      else
      {
        output = sub(input->ch_int_arr, input->ch_dec_arr, this->ch_int_arr, this->ch_dec_arr);
        output->positive = false;
      }
    }
    //負減負
    else if(!this->positive && !input->positive)
    {
      if(bigger(this, input))
      {
        output = sub(this->ch_int_arr, this->ch_dec_arr, input->ch_int_arr, input->ch_dec_arr);;
        output->positive = false;
      }
      else
      {
        output = sub(input->ch_int_arr, input->ch_dec_arr, this->ch_int_arr, this->ch_dec_arr);
        output->positive = true;
      }
    }

    //使用banker's rounding
    //banker_rounding(output->ch_int_arr, output->ch_dec_arr);

    return output;
  }

  BigDecimal* operator*(const BigDecimal *input) const
  {
    int decimal_digit = this->ch_dec_arr.length() + input->ch_dec_arr.length();
    int calc[SIZE] = {0}, arr_index = 0;
    std::string num_a, num_b, res, buf;
    num_a = this->ch_int_arr + this->ch_dec_arr;
    num_b = input->ch_int_arr + input->ch_dec_arr;


    //std::cout << "num_a:" << num_a << std::endl;
    //std::cout << "num_b:" << num_b << std::endl;
    //std::cout << "decimal_digit:" << decimal_digit << std::endl;

    arr_index = num_a.length() + num_b.length();

    //std::cout << "multply 1\n";

    for(int i = num_a.length()-1;i >= 0;i--)
    {
      for(int j = num_b.length()-1;j >= 0;j--)
      {
        int buf_a = num_a[i] - '0';
        int buf_b = num_b[j] - '0';
        //std::cout << "i:" << i  << " j:" << j << std::endl;
        //std::cout << "buf_a:" << buf_a << "buf_b:" << buf_b << std::endl;


        calc[num_a.length()-1-i+num_b.length()-1-j] += (buf_a * buf_b);
        //std::cout << "calc:" << calc[strlen(num_a)-1-i+strlen(num_b)-1-j] << std::endl;
      }
    }

    //std::cout << "multply 2\n";
    int carry = 0;
    for(int i = 0;i < arr_index;i++)
    {
      calc[i] += carry;
      carry = calc[i] / 10;
      calc[i] %= 10;

      //std::cout << "calc:" << calc[i] << std::endl;
      //std::cout << "carry:" << carry << std::endl;
    }


    bool not_zero = true;
    //將陣列轉成字串
    for(int i = arr_index;i >= 0;i--)
    {
      //std::cout << "in for\n";
      //最高位數為0
      if(i == arr_index && calc[i] == 0)
        not_zero = false;
      else if(calc[i] != 0)
        not_zero = true;

      if(not_zero)
      {
        res += std::to_string(calc[i]);
      }
      //std::cout << "put num:"<< calc[i] << std::endl;
    }

    //全部都是零
    if(!not_zero)
      {
        res += std::to_string(0);
      }
    
    //std::cout << "copy string\n";
    //std::cout << res << std::endl;


    std::string res_int, res_dec;

    //此數為零
    if(res.length() == 1 && res[0] == '0')
    {
      res_int += "0";
      res_dec += "0";
    }
    //此數為小於一
    else if(res.length() <= decimal_digit)
    {
      for(int i = 0;i < decimal_digit-res.length();i++)
      {
        res_dec += "0";
      }
      res_int += "0";

      res_dec += res;
    }
    //此數大於一
    else
    {
      res_int += res.substr(0, res.length()-decimal_digit);
      res_dec += res.substr(res.length()-decimal_digit);
    }

    //如果小數位數太多(大於25，拿掉多餘的)
    while(res_dec.length() > 25)
    {
      res_dec.resize(25);
    }

    
    BigDecimal *r = new BigDecimal(res_int, res_dec);
    if(this->positive == true && input-> positive == true || this->positive == false && input->positive == false)
      r->positive = true;
    else
      r->positive = false;

    //std::cout << "multply done.\n";

    return r;
  }
  
  BigDecimal* operator^(const BigDecimal *input) const
  {
    //整數指數
    if(input->ch_dec_arr.length() == 1 && input->ch_dec_arr[0] == '0')
    {

    }

    BigDecimal ln_calc(this->ch_int_arr,this->ch_dec_arr), num_1("1","0"), num_2("2","0");
    BigDecimal *buf_1 = ln_calc - &num_1, *buf_2 = ln_calc + &num_1;
    BigDecimal *ln_numerator = *buf_1 / buf_2, *pow_ln_numerator;
    
    pow_ln_numerator = *ln_numerator * &num_1;
    

    BigDecimal *ln_denominator = new BigDecimal("1","0");
    BigDecimal *ln_result = new BigDecimal("0","0");

    BigDecimal *temp_place;

    //計算ln(目前計算3000次，看準不準確)
    for(int round = 0;round < 3000;round++)
    {
      if(round != 0)
      {
        for(int pow_2 = 0 ; pow_2 < 2;pow_2++)
        {
          //std::cout << "\nstart\n";
          temp_place = *pow_ln_numerator * ln_numerator;
          delete pow_ln_numerator;
          pow_ln_numerator = temp_place;
          //std::cout << "\nend\n";
          //std::cout << "pow_ln_numerator:" << pow_ln_numerator->ch_int_arr << "." << pow_ln_numerator->ch_dec_arr << std::endl;
        }

        temp_place = *ln_denominator + &num_2;
        delete ln_denominator;
        ln_denominator = temp_place;
      }

      BigDecimal *buf_3 = *pow_ln_numerator / ln_denominator;
      temp_place = *ln_result + buf_3;
      delete ln_result;
      ln_result = temp_place;
      delete buf_3;
      
      //std::cout << "integer:" << result->ch_int_arr << std::endl;
      //std::cout << "dec:" << result->ch_dec_arr << std::endl;
    }

    ln_result = *ln_result * &num_2;
    //std::cout << "integer:" << ln_result->ch_int_arr << std::endl;
    //std::cout << "dec:" << ln_result->ch_dec_arr << std::endl;


    BigDecimal *e_power = *ln_result * input;

    BigDecimal *counter = new BigDecimal("3000","0");
    BigDecimal *result = new BigDecimal("1","0");

    for(int round = 3000;round > 0;round--)
    {
      //std::cout << "round:" << round << std::endl;
      BigDecimal *buf_4 = *e_power * result;
      delete result;
      temp_place = *buf_4 / counter;
      delete buf_4;
      buf_4 = temp_place;
      temp_place = *buf_4 + &num_1;
      delete buf_4;
      result = temp_place;

      temp_place = *counter - &num_1;
      delete counter;
      counter = temp_place;
    }

    //for (i = n - 1, sum = 1; i > 0; --i )
    //  sum = 1 + x * sum / i; 
    delete(e_power);
    delete(counter);

    std::cout << "final result:" << result->ch_int_arr << "." << result->ch_dec_arr << std::endl;

    return result;
  }

  /*
  1.將小數改成整數，再開始進行除法
  2.處理整數部分
  3.處理小數部分
  */
  BigDecimal* operator/(BigDecimal *input)
  {
    std::string input_a, input_b, buf;

    //複製字串到input_a & input_b
    input_a = this->ch_int_arr + this->ch_dec_arr;
    input_b = input->ch_int_arr + input->ch_dec_arr;

    //預期a比b還要多小數
    int difference = this->ch_dec_arr.length() - input->ch_dec_arr.length();
    if(difference > 0)
    {
      for(int i = 0;i < difference;i++)
      {
        //std::cout << "fill 0 on input_b\n";
        input_b += "0";
      }
    }
    else if(difference < 0)
    {
      for(int i = 0;i < abs(difference);i++)
      {
        //std::cout << "fill 0 on input_a\n";
        input_a += "0";
      }
    }

    //std::cout << "before remove 0 input_a:" << input_a << std::endl;
    //std::cout << "before remove 0 input_b:" << input_b << std::endl;

    //把input_a & input_b 前面的零拿掉
    while(input_a[0] == '0')
    {
      input_a.erase(0, 1);
      //std::cout << "in while input_a:" << input_a << std::endl;
    }
    while(input_b[0] == '0')
    {
      input_a.erase(0, 1);
      //std::cout << "in while input_b:" << input_b << std::endl;
    }

    //std::cout << "after remove 0 input_a:" << input_a << std::endl;
    //std::cout << "after remove 0 input_b:" << input_b << std::endl;


    //到這邊，已經有整數的input_a & input_b
    //將input_a當作被除數，input_b當作除數
    std::string::iterator start = input_a.begin(), end = input_a.begin();
    std::string res_int, res_dec;
    
    //先處理整數部分
    while(end != input_a.end())
    {
      std::string::iterator not_zero_start = start;
      std::string buf2;

      while(*not_zero_start == '0' && not_zero_start < end)
        not_zero_start++;

      buf2 += std::string(not_zero_start, not_zero_start+(end-not_zero_start)+1);
      //可以除

      //std::cout << "compare num:" << buf2 << std::endl;

      if(bigger_integer(&buf2, &input_b))
      {
        for(int i = 1;i < 10;i++)
        {
          BigDecimal multi_a(input_b, "0"), multi_b(std::to_string(i),"0");
          //std::cout << multi_a.ch_int_arr << " " << multi_b.ch_int_arr << std::endl;
          BigDecimal *multi_res = multi_a * &multi_b, *buf;
          //額外加一份，用作比大小
          buf = *multi_res + &multi_a;
          delete multi_res;
          multi_res = buf;

          //std::cout << "multiply num:" << multi_res->ch_int_arr << std::endl;

          //除數的乘積大於所選定的被除數
          if(bigger_integer(&multi_res->ch_int_arr, &buf2) && !equal(&multi_res->ch_int_arr, &buf2))
          {
            //把比大小的額外一倍減掉
            buf = *multi_res - &multi_a;
            delete multi_res;
            multi_res = buf;

            BigDecimal subtract_b = BigDecimal(buf2,"0");
            BigDecimal *after_sub = subtract_b - multi_res;

            //std::cout << "sub num:" << after_sub->ch_int_arr << std::endl;

            int sub_len = after_sub->ch_int_arr.length() - 1;
            //把減下的數字放回被除數中
            for(auto iter = end;iter >= start;iter--, sub_len--)
            {
              if(sub_len >= 0)
                *iter = after_sub->ch_int_arr[sub_len];
              else
                *iter = '0';
            }

            delete after_sub;

            //std::cout << "input_a:" << input_a << std::endl;

            //放置數到商中
            res_int += std::to_string(i);

            while(*start == '0' && start != end)
              start++;

            end++;

            break;
          }
        }
      }
      //除不了
      else
      {
        end++;
        res_int += "0";
      }
    }
    
    int start_num = start-input_a.begin(), end_num = end-input_a.begin();

    input_a += "0";
    //更新iterator
    start = input_a.begin() + start_num;
    end = input_a.begin() + end_num;
    //std::cout << "decimal part\n";
    //std::cout << "start_num:" << start_num << std::endl;
    //std::cout << "end_num:" << end_num << std::endl;

    
    //再處理小數部分
    while(res_dec.length() < 25)
    {
      std::string buf2;
      std::string::iterator not_zero_start = start;

      while(*not_zero_start == '0' && not_zero_start < end)
        not_zero_start++;

      buf2 += std::string(not_zero_start, not_zero_start+(end-not_zero_start)+1);
      //可以除

      //std::cout << "compare num:" << buf2 << std::endl;

      if(bigger_integer(&buf2, &input_b))
      {
        for(int i = 1;i < 10;i++)
        {
          //std::cout << "input_b:" << input_b << "end" << std::endl;
          BigDecimal multi_a(input_b, "0"), multi_b(std::to_string(i),"0");
          //std::cout << multi_a.ch_int_arr << " " << multi_b.ch_int_arr << std::endl;
          BigDecimal *multi_res = multi_a * &multi_b, *buf;
          //額外加一份，用作比大小
          buf = *multi_res + &multi_a;
          delete multi_res;
          multi_res = buf; 

          //std::cout << "multiply num:" << multi_res->ch_int_arr << std::endl;

          //除數的乘積大於所選定的被除數
          if(bigger_integer(&multi_res->ch_int_arr, &buf2) && !equal(&multi_res->ch_int_arr, &buf2))
          {
            //把比大小的額外一倍減掉
            buf = *multi_res - &multi_a;
            delete multi_res;
            multi_res = buf;

            BigDecimal subtract_b = BigDecimal(buf2,"0");
            BigDecimal *after_sub = subtract_b - multi_res;

            //std::cout << "sub num:" << after_sub->ch_int_arr << std::endl;

            int sub_len = after_sub->ch_int_arr.length() - 1;
            //把減下的數字放回被除數中
            for(auto iter = end;iter >= start;iter--, sub_len--)
            {
              if(sub_len >= 0)
                *iter = after_sub->ch_int_arr[sub_len];
              else
                *iter = '0';
            }

            //std::cout << "input_a:" << input_a << std::endl;

            //放置數到商中
            res_dec += std::to_string(i);

            while(*start == '0' && start != end)
              start++;

            end++;

            break;
          }
        }
      }
      //除不了
      else
      {
        end++;
        res_dec += "0";
      }

      int start_num = start-input_a.begin(), end_num = end-input_a.begin();
      //std::cout << "res_dec.len:" << res_dec.length() << std::endl;
      //std::cout << res_dec.capacity() << std::endl;
      //std::cout << "start_num:" << start_num << std::endl;
      //std::cout << "end_num:" << end_num << std::endl;
      //額外增加一位
      input_a += "0";

      start = input_a.begin() + start_num;
      end = input_a.begin() + end_num;

    }
    

    //清除整數前的0
    std::string::iterator not_zero_place = res_int.begin();
    while(*not_zero_place == '0' && not_zero_place != res_int.end())
      not_zero_place++;
    
    //全部是0
    if(not_zero_place == res_int.end())
    {
      res_int = "0";
    }
    else
    {
      res_int = std::string(not_zero_place, res_int.end());
    }

    BigDecimal *result = new BigDecimal(res_int, res_dec);
    result->positive = (this->positive + input->positive) % 2 == 0 ? true : false;
    return result;
  }

  //預期為兩個正數加法
  BigDecimal* add(std::string a_i_arr, std::string a_d_arr , std::string b_i_arr, std::string b_d_arr) const
  {
    //結果字串
    std::string res_int, res_dec;

    //計算用的陣列
    int calc_int_arr[SIZE]={0}, calc_dec_arr[SIZE]={0};
    //紀錄進位與index
    int int_carry = 0, dec_carry = 0, i_arr_index = 0, d_arr_index = 0;

    //整數運算
    for(int a_len = a_i_arr.length()-1, b_len = b_i_arr.length()-1
      ;a_len >= 0 || b_len >= 0;a_len--, b_len--, i_arr_index++)
      {
        //如果該位數為空，就回傳0
        int buf_a = a_len >= 0 ? a_i_arr[a_len] - '0' : 0; 
        int buf_b = b_len >= 0 ? b_i_arr[b_len] - '0' : 0;

        calc_int_arr[i_arr_index] = buf_a + buf_b + int_carry;
        int_carry = calc_int_arr[i_arr_index] / 10;
        calc_int_arr[i_arr_index] %= 10;

        //std::cout << "a_len:" << a_len << std::endl; 
        //std::cout << "b_len:" << b_len << std::endl; 
        //std::cout << "index:" << i_arr_index << std::endl; 
      }

    //額外進位情況，ex. 1+999
    if(int_carry == 1)
        calc_int_arr[i_arr_index] = 1;

    //std::cout << "Integer add complete\n";

    //小數運算
    for(int iter = a_d_arr.length() > b_d_arr.length() ? a_d_arr.length()-1 : b_d_arr.length()-1;
      iter >= 0;iter--, d_arr_index++)
      {
        
        int buf_a = iter <= a_d_arr.length()-1 ? a_d_arr[iter] - '0' : 0; 
        int buf_b = iter <= b_d_arr.length()-1 ? b_d_arr[iter] - '0' : 0;

        calc_dec_arr[iter] = buf_a + buf_b + dec_carry;
        dec_carry = calc_dec_arr[iter] / 10;
        calc_dec_arr[iter] %= 10;

        //std::cout << strlen(a_d_arr) << std::endl;
        //std::cout << strlen(b_d_arr) << std::endl;
        //std::cout << iter << std::endl;
      }

      //std::cout << "Decimal add complete\n";


    //額外進位情況，ex. 0.999+9.001 or 0.999+8.001
    if(dec_carry == 1)
    {
      calc_int_arr[0] += 1;
      int nine_iter = 0;
      while(calc_int_arr[nine_iter] == 10)
      {
        calc_int_arr[nine_iter] %= 10;
        calc_int_arr[nine_iter+1] += 1;
        nine_iter++;
      }
    }

    //將整數陣列轉成字串
    for(int i = i_arr_index;i >= 0;i--)
    {
      //最高位數為0
      if(i == i_arr_index && calc_int_arr[i] == 0)
        continue;

      res_int += std::to_string(calc_int_arr[i]);
      //std::cout << "put num:"<< calc_int_arr[i] << std::endl;
    }

    //將小數陣列轉成字串
    for(int i = 0;i < d_arr_index;i++)
    {
      res_dec += std::to_string(calc_dec_arr[i]);
      //std::cout << "calc_dec_arr:" << calc_dec_arr[i] << std::endl;
    }

    //std::cout << "integer:" << res_int << "\n";
    //std::cout << "decimal:" << res_dec << "\n";

    BigDecimal *r = new BigDecimal(res_int, res_dec);

    //std::cout << "Plus done.\n";
    return r;
  }

  
  /*
  1.先計算小數減法，如果小數需要借位(ex. 12.888-1.999)，變數加一
  (小數index為從小到大)
  2.再計算整數減法，順便檢查是否需要額外借位
  (整數index為從大到小)
  3.把整數陣列轉成字串
  (需要注意是否前方為0，ex. 100-99，前方的兩個零要忽略)
  (只有最高位數為0時，我們才需要關注此狀況，ex. 10002-1，其中的0是必要的)
  (也有可能會有剛好為0的情況，ex. 100-100)
  4.把小數陣列轉成字串
  */
  //預期為兩個正數減法(大減小)
  BigDecimal* sub(std::string a_i_arr, std::string a_d_arr, std::string b_i_arr, std::string b_d_arr) const
  {
    //結果字串
    std::string res_int, res_dec;

    //計算用的陣列
    int calc_int_arr[SIZE]={0}, calc_dec_arr[SIZE]={0};
    //紀錄進位與index
    int int_borrow = 0, i_arr_index = 0, d_arr_index = 0;

    //小數運算
    for(int iter = a_d_arr.length() > b_d_arr.length() ? a_d_arr.length()-1 : b_d_arr.length()-1;
      iter >= 0;iter--, d_arr_index++)
      {
        
        int buf_a = iter <= a_d_arr.length()-1 ? a_d_arr[iter] - '0' : 0; 
        int buf_b = iter <= b_d_arr.length()-1 ? b_d_arr[iter] - '0' : 0;

        calc_dec_arr[iter] += buf_a - buf_b;
        //需要和整數借位
        if(calc_dec_arr[iter] < 0 && iter == 0)
        {
          calc_dec_arr[iter] += 10;
          int_borrow = 1;
        }
        //小數正常借位
        else if(calc_dec_arr[iter] < 0)
        {
          calc_dec_arr[iter] += 10;
          calc_dec_arr[iter-1] -= 1;
        }

        //std::cout << strlen(a_d_arr) << std::endl;
        //std::cout << strlen(b_d_arr) << std::endl;
        //std::cout << iter << std::endl;
      }

      //std::cout << "Decimal subtract complete\n";

    //整數運算
    for(int a_len = a_i_arr.length()-1, b_len = b_i_arr.length()-1
      ;a_len >= 0 || b_len >= 0;a_len--, b_len--, i_arr_index++)
      {
        //如果該位數為空，就回傳0
        int buf_a = a_len >= 0 ? a_i_arr[a_len] - '0' : 0; 
        int buf_b = b_len >= 0 ? b_i_arr[b_len] - '0' : 0;

        calc_int_arr[i_arr_index] += buf_a - buf_b - int_borrow;
        if(calc_int_arr[i_arr_index] < 0)
        {
          calc_int_arr[i_arr_index] += 10;
          int_borrow = 1;
        }
        else
        {
          int_borrow = 0;
        }

        //std::cout << "calc_int_arr:" << calc_int_arr[i_arr_index] << "\n";

        //std::cout << "a_len:" << a_len << std::endl; 
        //std::cout << "b_len:" << b_len << std::endl; 
        //std::cout << "index:" << i_arr_index << std::endl; 
      }

    //std::cout << "Integer subtract complete\n";


    bool not_zero = true;
    //將整數陣列轉成字串
    for(int i = i_arr_index;i >= 0;i--)
    {
      //最高位數為0
      if(i == i_arr_index && calc_int_arr[i] == 0)
        not_zero = false;
      else if(calc_int_arr[i] != 0)
        not_zero = true;

      if(not_zero)
      {
        res_int += std::to_string(calc_int_arr[i]);
      }
      //std::cout << "put num:"<< calc_int_arr[i] << std::endl;
    }

    //全部都是零
    if(!not_zero)
      {
        res_int += std::to_string(0);
      }

    //將小數陣列轉成字串
    for(int i = 0;i < d_arr_index;i++)
    {
      res_dec += std::to_string(calc_dec_arr[i]);
      //std::cout << "calc_dec_arr:" << calc_dec_arr[i] << std::endl;
    }

    //std::cout << "integer:" << res_int << "\n";
    //std::cout << "decimal:" << res_dec << "\n";

    BigDecimal *r = new BigDecimal(res_int, res_dec);

    //std::cout << "Subtract done.\n";
    return r;
  }

  static bool check_all_zero(std::string int_arr, std::string dec_arr)
  {
    for(int i = 0;i < int_arr.length();i++)
    {
      if(int_arr[i] != '0')
        return false;
    }

    for(int i = 0;i < dec_arr.length();i++)
    {
      if(dec_arr[i] != '0')
        return false;
    }

    return true;
  }

  friend std::istream &operator>>(std::istream &in, BigDecimal *data)
  {
    std::string input;
    in >> input;

    //此數為負數
    if(input[0] == '-')
    {
      //std::cout << "This is negative number\n";
      input.erase(0, 1);
      data->positive = false;
    }
    else
    {
      data->positive = true;
    }


    //把整數與小數切割
    set_substr(&input, &data->ch_int_arr, &data->ch_dec_arr);

    //std::cout << "int_arr"<<data->ch_int_arr << std::endl;
    //std::cout << "dec_arr"<<data->ch_dec_arr << std::endl;
    return in;
  }

  friend std::ostream &operator<<(std::ostream &out, BigDecimal *bigDecimal)
  {
    if(bigDecimal == NULL)
      return out;
    
    banker_rounding(&bigDecimal->ch_int_arr, &bigDecimal->ch_dec_arr);

    if(bigDecimal->positive == false && !check_all_zero(bigDecimal->ch_int_arr, bigDecimal->ch_dec_arr))
      std::cout << "-";
    if(bigDecimal->ch_dec_arr.length() == 1 && bigDecimal->ch_dec_arr[0] == '0')
      out << bigDecimal->ch_int_arr << ".0" << bigDecimal->ch_dec_arr << std::endl;
    else
      out << bigDecimal->ch_int_arr << "." << bigDecimal->ch_dec_arr << std::endl;

    return out;
  }

  

  private:
  std::string ch_int_arr, ch_dec_arr;
  bool positive = true;
};




int main() {
  BigDecimal *bigDecimal1 = new BigDecimal();
  BigDecimal *bigDecimal2 = new BigDecimal();
  char operation;
  while(std::cin >> bigDecimal1 >> operation >> bigDecimal2) {
    switch (operation) {
    case '+':
      std::cout << (*bigDecimal1 + bigDecimal2);
      break;
    case '-':
      std::cout << (*bigDecimal1 - bigDecimal2);
      break;
    case '*':
      std::cout << (*bigDecimal1 * bigDecimal2);
      break;
    case '/':
      std::cout << (*bigDecimal1 / bigDecimal2);
      break;
    case '^':
      std::cout << (*bigDecimal1 ^ bigDecimal2);
      break;
    default:
      break;
    }
  }
  return 0;
}
