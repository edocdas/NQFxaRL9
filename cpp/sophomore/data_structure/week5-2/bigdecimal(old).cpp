#include<iostream>
#include<cstring>

class BigDecimal
{
  public:
  BigDecimal() = default;
  BigDecimal(const char *int_arr, const char *dec_arr)
  {
    //this->ch_int_arr = new char[10000];
    //this->ch_dec_arr = new char[10000];

    strcpy(this->ch_int_arr, int_arr);
    strcpy(this->ch_dec_arr, dec_arr);
  }
  BigDecimal(const BigDecimal &input)
  {
    //this->ch_int_arr = new char[10000];
    //this->ch_dec_arr = new char[10000];

    strcpy(this->ch_int_arr, input.ch_int_arr);
    strcpy(this->ch_dec_arr, input.ch_dec_arr);
    this->positive = input.positive;
  }

  ~BigDecimal()
  {
    //delete []ch_int_arr;
    //delete []ch_dec_arr;
  }

  static void set_substr(char *input, char *in_int, char *in_dec)
  {
    //找點號
    char *dot = strstr(input, ".");

    //整數情況
    if(dot == NULL)
    {
      strcpy(in_int, input);
      strcpy(in_dec, "0\0");
    }
    else
    //小數情況
    {
      strncpy(in_int, input, dot-input);
      strcpy(in_dec, dot+1);
    }
  }

  bool bigger(const BigDecimal *a, const BigDecimal *b) const
  {
    //檢查整數
    if(strlen(a->ch_int_arr) > strlen(b->ch_int_arr))
      return true;
    
    if(strlen(a->ch_int_arr) < strlen(b->ch_int_arr))
      return false;

    for(int i = 0;i <= strlen(a->ch_int_arr) || i << strlen(b->ch_int_arr);i++)
    {
      if(a->ch_int_arr[i] > b->ch_int_arr[i])
        return true;
      if(a->ch_int_arr[i] < b->ch_int_arr[i])
        return false;
    }

    //檢查小數
    if(strlen(a->ch_dec_arr) > strlen(b->ch_dec_arr))
      return true;
    
    if(strlen(a->ch_dec_arr) < strlen(b->ch_dec_arr))
      return false;

    for(int i = 0;i <= strlen(a->ch_dec_arr) || i << strlen(b->ch_dec_arr);i++)
    {
      if(a->ch_dec_arr[i] > b->ch_dec_arr[i])
        return true;
      if(a->ch_dec_arr[i] < b->ch_dec_arr[i])
        return false;
    }

    //兩者相同
    return true;
  }

  bool bigger_integer(const char *a_int, const char *b_int)
  {
    if(strlen(a_int) > strlen(b_int))
      return true;
    else if(strlen(a_int) < strlen(b_int))
      return false;
    else
    {
      for(int i = 0;i < strlen(a_int);i++)
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

  bool equal(const char *a_int, const char *b_int)
  {
    if(strlen(a_int) > strlen(b_int))
      return false;
    else if(strlen(a_int) < strlen(b_int))
      return false;
    else
    {
      for(int i = 0;i < strlen(a_int);i++)
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


  void check_9(char *ch, int iter, int *bonus)
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
  void banker_rounding(char *i_arr, char *d_arr)
  {
    int bonus = 0;
    char *dot_place = 0;
    char ch[10000];

    strcpy(ch, i_arr);
    strcpy(ch+strlen(ch), ".");
    strcpy(ch+strlen(ch), d_arr);
    dot_place = strchr(ch, '.');
    

    for(int i = strlen(ch)-1; ch[i-2] != '.' && ch[i-1] != '.';i--)
    {
      if(ch[i] - '0' > 5 || (ch[i] - '0' == 5 && (ch[i-1] - '0') % 2 == 1))
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
        char buf[10000];
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
    int decimal_digit = strlen(this->ch_dec_arr) + strlen(input->ch_dec_arr);
    int calc[10000] = {0}, arr_index = 0;
    char num_a[10000], num_b[10000], res[10000], buf[10000];
    memset(res, 0, 10000);
    strcpy(num_a, this->ch_int_arr);
    strcpy(num_a+strlen(num_a), this->ch_dec_arr);
    strcpy(num_b, input->ch_int_arr);
    strcpy(num_b+strlen(num_b), input->ch_dec_arr);

    //std::cout << "num_a:" << num_a << std::endl;
    //std::cout << "num_b:" << num_b << std::endl;
    //std::cout << "decimal_digit:" << decimal_digit << std::endl;

    arr_index = strlen(num_a) + strlen(num_b);

    //std::cout << "multply 1\n";

    for(int i = strlen(num_a)-1;i >= 0;i--)
    {
      for(int j = strlen(num_b)-1;j >= 0;j--)
      {
        int buf_a = num_a[i] - '0';
        int buf_b = num_b[j] - '0';
        //std::cout << "i:" << i  << " j:" << j << std::endl;
        //std::cout << "buf_a:" << buf_a << "buf_b:" << buf_b << std::endl;


        calc[strlen(num_a)-1-i+strlen(num_b)-1-j] += (buf_a * buf_b);
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
      sprintf(res+strlen(res), "%d", calc[i]);
      }
      //std::cout << "put num:"<< calc[i] << std::endl;
    }

    //全部都是零
    if(!not_zero)
      {
      sprintf(res+strlen(res), "%d", 0);
      }
    
    //std::cout << "copy string\n";
    //std::cout << res << std::endl;


    char res_int[10000], res_dec[10000];
    memset(res_int, 0, 10000);
    memset(res_dec, 0, 10000);

    //此數為零
    if(strlen(res) == 1 && res[0] == '0')
    {
      strcpy(res_int, "0\0");
      strcpy(res_dec, "0\0");
    }
    //此數為小於一
    else if(strlen(res) <= decimal_digit)
    {
      for(int i = 0;i < decimal_digit-strlen(res);i++)
      {
        strcpy(res_dec+strlen(res_dec), "0\0");
      }
      strcpy(res_int, "0\0");

      strcpy(res_dec+strlen(res_dec), res);
    }
    //此數大於一
    else
    {
      strncpy(res_int, res, strlen(res)-decimal_digit);
      strcpy(res_dec, res+strlen(res)-decimal_digit);
    }

    //如果小數位數太多(大於25，拿掉多餘的)
    while(strlen(res_dec) > 25)
    {
      res_dec[strlen(res_dec)-1] = '\0';
    }

    
    BigDecimal *r = new BigDecimal(res_int, res_dec);
    if(this->positive == true && input-> positive == true || this->positive == false && input->positive == false)
      r->positive = true;
    else
      r->positive = false;

    //std::cout << "multply done.\n";

    return r;
  }
  
  BigDecimal* operator^(BigDecimal *input)
  {
    BigDecimal ln_calc(this->ch_int_arr,this->ch_dec_arr), num_1("1","0"), num_2("2","0");
    BigDecimal *buf_1 = ln_calc - &num_1, *buf_2 = ln_calc + &num_1;
    BigDecimal *ln_numerator = *buf_1 / buf_2, *pow_ln_numerator;
    
    pow_ln_numerator = *ln_numerator * &num_1;
    

    BigDecimal *ln_denominator = new BigDecimal("1","0");
    BigDecimal *ln_result = new BigDecimal("0","0");


    //計算ln(目前計算3000次，看準不準確)
    for(int round = 0;round < 3000;round++)
    {
      if(round != 0)
      {
        for(int pow_2 = 0 ; pow_2 < 2;pow_2++)
        {
          //std::cout << "\nstart\n";
          pow_ln_numerator = *pow_ln_numerator * ln_numerator;
          //std::cout << "\nend\n";
          //std::cout << "pow_ln_numerator:" << pow_ln_numerator->ch_int_arr << "." << pow_ln_numerator->ch_dec_arr << std::endl;
        }

        ln_denominator = *ln_denominator + &num_2;
      }

      BigDecimal *buf_3 = *pow_ln_numerator / ln_denominator;
      ln_result = *ln_result + buf_3;
      //std::cout << "integer:" << result->ch_int_arr << std::endl;
      //std::cout << "dec:" << result->ch_dec_arr << std::endl;
    }

    ln_result = *ln_result * &num_2;
    std::cout << "integer:" << ln_result->ch_int_arr << std::endl;
    std::cout << "dec:" << ln_result->ch_dec_arr << std::endl;


    BigDecimal *e_power = *ln_result * input;

    BigDecimal *counter = new BigDecimal("3000","0");
    BigDecimal *result = new BigDecimal("1","0");

    for(int round = 3000;round > 0;round--)
    {
      std::cout << "round:" << round << std::endl;
      BigDecimal *buf_4 = *e_power * result;
      buf_4 = *buf_4 / counter;
      buf_4 = *buf_4 + &num_1;
      result = buf_4;

      counter = *counter - &num_1;
    }

    //for (i = n - 1, sum = 1; i > 0; --i )
    //  sum = 1 + x * sum / i; 

    std::cout << "final result:" << result << std::endl;

    return result;
  }

  /*
  1.將小數改成整數，再開始進行除法
  2.處理整數部分
  3.處理小數部分
  */
  BigDecimal* operator/(BigDecimal *input)
  {
    char input_a[10000], input_b[10000], buf[10000];
    memset(input_a, 0, 10000);
    memset(input_b, 0, 10000);

    //複製字串到input_a & input_b
    strcpy(input_a, this->ch_int_arr);
    strcpy(input_a+strlen(input_a), this->ch_dec_arr);
    strcpy(input_b, input->ch_int_arr);
    strcpy(input_b+strlen(input_b), input->ch_dec_arr);

    //預期a比b還要多小數
    int difference = strlen(this->ch_dec_arr) - strlen(input->ch_dec_arr);
    if(difference > 0)
    {
      for(int i = 0;i < difference;i++)
      {
        //std::cout << "fill 0 on input_b\n";
        strcpy(input_b+strlen(input_b), "0");
      }
    }
    else if(difference < 0)
    {
      for(int i = 0;i < abs(difference);i++)
      {
        //std::cout << "fill 0 on input_a\n";
        strcpy(input_a+strlen(input_a), "0");
      }
    }

    //std::cout << "before remove 0 input_a:" << input_a << std::endl;
    //std::cout << "before remove 0 input_b:" << input_b << std::endl;

    //把input_a & input_b 前面的零拿掉
    while(input_a[0] == '0')
    {
      strcpy(buf, input_a+1);
      strcpy(input_a, buf);
      //std::cout << "in while input_a:" << input_a << std::endl;
    }
    while(input_b[0] == '0')
    {
      strcpy(buf, input_b+1);
      strcpy(input_b, buf);
      //std::cout << "in while input_b:" << input_b << std::endl;
    }

    //std::cout << "after remove 0 input_a:" << input_a << std::endl;
    //std::cout << "after remove 0 input_b:" << input_b << std::endl;


    //到這邊，已經有整數的input_a & input_b
    //將input_a當作被除數，input_b當作除數
    char *start = input_a, *end = input_a;
    char res_int[10000], res_dec[10000];
    memset(res_int, 0, 10000);
    memset(res_dec, 0, 10000);
    
    //先處理整數部分
    while(end != input_a + strlen(input_a))
    {
      char buf2[10000], *not_zero_start = start;
      memset(buf2, 0 , 10000);

      while(*not_zero_start == '0' && not_zero_start < end)
        not_zero_start++;

      strncpy(buf2, not_zero_start, end-not_zero_start+1);
      //可以除

      //std::cout << "compare num:" << buf2 << std::endl;

      if(bigger_integer(buf2, input_b))
      {
        for(int i = 1;i < 10;i++)
        {
          char select_num = i + '0', multi_num[3] = {select_num, '\0'};

          BigDecimal multi_a(input_b, "0"), multi_b(multi_num,"0");
          //std::cout << multi_a.ch_int_arr << " " << multi_b.ch_int_arr << std::endl;
          BigDecimal *multi_res = multi_a * &multi_b;
          //額外加一份，用作比大小
          multi_res = *multi_res + &multi_a; 

          //std::cout << "multiply num:" << multi_res->ch_int_arr << std::endl;

          //除數的乘積大於所選定的被除數
          if(bigger_integer(multi_res->ch_int_arr, buf2) && !equal(multi_res->ch_int_arr, buf2))
          {
            //把比大小的額外一倍減掉
            multi_res = *multi_res - &multi_a;

            BigDecimal subtract_b = BigDecimal(buf2,"0");
            BigDecimal *after_sub = subtract_b - multi_res;

            //std::cout << "sub num:" << after_sub->ch_int_arr << std::endl;

            int sub_len = strlen(after_sub->ch_int_arr) - 1;
            //把減下的數字放回被除數中
            for(char * iter = end;iter >= start;iter--, sub_len--)
            {
              if(sub_len >= 0)
                *iter = after_sub->ch_int_arr[sub_len];
              else
                *iter = '0';
            }

            //std::cout << "input_a:" << input_a << std::endl;

            //放置數到商中
            strcpy(res_int+strlen(res_int), multi_num);

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
        strcpy(res_int+strlen(res_int), "0");
      }
    }

    *end = '0';
    //std::cout << "decimal part\n";

        
    //再處理小數部分
    while(strlen(res_dec) < 20)
    {
      char buf2[10000], *not_zero_start = start;
      memset(buf2, 0 , 10000);

      while(*not_zero_start == '0' && not_zero_start < end)
        not_zero_start++;

      strncpy(buf2, not_zero_start, end-not_zero_start+1);
      //可以除

      //std::cout << "compare num:" << buf2 << std::endl;

      if(bigger_integer(buf2, input_b))
      {
        for(int i = 1;i < 10;i++)
        {
          char select_num = i + '0', multi_num[3] = {select_num, '\0'};

          BigDecimal multi_a(input_b, "0"), multi_b(multi_num,"0");
          //std::cout << multi_a.ch_int_arr << " " << multi_b.ch_int_arr << std::endl;
          BigDecimal *multi_res = multi_a * &multi_b;
          //額外加一份，用作比大小
          multi_res = *multi_res + &multi_a; 

          //std::cout << "multiply num:" << multi_res->ch_int_arr << std::endl;

          //除數的乘積大於所選定的被除數
          if(bigger_integer(multi_res->ch_int_arr, buf2) && !equal(multi_res->ch_int_arr, buf2))
          {
            //把比大小的額外一倍減掉
            multi_res = *multi_res - &multi_a;

            BigDecimal subtract_b = BigDecimal(buf2,"0");
            BigDecimal *after_sub = subtract_b - multi_res;

            //std::cout << "sub num:" << after_sub->ch_int_arr << std::endl;

            int sub_len = strlen(after_sub->ch_int_arr) - 1;
            //把減下的數字放回被除數中
            for(char * iter = end;iter >= start;iter--, sub_len--)
            {
              if(sub_len >= 0)
                *iter = after_sub->ch_int_arr[sub_len];
              else
                *iter = '0';
            }

            //std::cout << "input_a:" << input_a << std::endl;

            //放置數到商中
            strcpy(res_dec+strlen(res_dec), multi_num);

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
        strcpy(res_dec+strlen(res_dec), "0");
      }

      //額外增加一位
      *end = '0';
    }
    
    //清除整數前的0
    char *not_zero_place = res_int;
    while(*not_zero_place == '0')
      not_zero_place++;
    
    //全部是0
    if(*not_zero_place == '\0')
    {
      strcpy(buf, "0");
      strcpy(res_int, buf);
    }
    else
    {
      strcpy(buf, not_zero_place);
      strcpy(res_int, buf);
    }

    BigDecimal *result = new BigDecimal(res_int, res_dec);
    result->positive = (this->positive + input->positive) % 2 == 0 ? true : false;
    return result;
  }

  //預期為兩個正數加法
  BigDecimal* add(const char *a_i_arr, const char *a_d_arr , const char *b_i_arr, const char *b_d_arr) const
  {
    //結果字串
    char res_int[10000], res_dec[10000];
    memset(res_int, 0, 10000);
    memset(res_dec, 0, 10000);

    //計算用的陣列
    int calc_int_arr[10000]={0}, calc_dec_arr[10000]={0};
    //紀錄進位與index
    int int_carry = 0, dec_carry = 0, i_arr_index = 0, d_arr_index = 0;

    //整數運算
    for(int a_len = strlen(a_i_arr)-1, b_len = strlen(b_i_arr)-1
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
    for(int iter = strlen(a_d_arr) > strlen(b_d_arr) ? strlen(a_d_arr)-1 : strlen(b_d_arr)-1;
      iter >= 0;iter--, d_arr_index++)
      {
        
        int buf_a = iter <= strlen(a_d_arr)-1 ? a_d_arr[iter] - '0' : 0; 
        int buf_b = iter <= strlen(b_d_arr)-1 ? b_d_arr[iter] - '0' : 0;

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

      sprintf(res_int+strlen(res_int), "%d", calc_int_arr[i]);
      //std::cout << "put num:"<< calc_int_arr[i] << std::endl;
    }

    //將小數陣列轉成字串
    for(int i = 0;i < d_arr_index;i++)
    {
      sprintf(res_dec+strlen(res_dec), "%d", calc_dec_arr[i]);
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
  BigDecimal* sub(const char *a_i_arr, const char *a_d_arr, const char *b_i_arr, const char *b_d_arr) const
  {
    //結果字串
    char res_int[10000], res_dec[10000];
    memset(res_int, 0, 10000);
    memset(res_dec, 0, 10000);

    //計算用的陣列
    int calc_int_arr[10000]={0}, calc_dec_arr[10000]={0};
    //紀錄進位與index
    int int_borrow = 0, i_arr_index = 0, d_arr_index = 0;

    //小數運算
    for(int iter = strlen(a_d_arr) > strlen(b_d_arr) ? strlen(a_d_arr)-1 : strlen(b_d_arr)-1;
      iter >= 0;iter--, d_arr_index++)
      {
        
        int buf_a = iter <= strlen(a_d_arr)-1 ? a_d_arr[iter] - '0' : 0; 
        int buf_b = iter <= strlen(b_d_arr)-1 ? b_d_arr[iter] - '0' : 0;

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
    for(int a_len = strlen(a_i_arr)-1, b_len = strlen(b_i_arr)-1
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
      sprintf(res_int+strlen(res_int), "%d", calc_int_arr[i]);
      }
      //std::cout << "put num:"<< calc_int_arr[i] << std::endl;
    }

    //全部都是零
    if(!not_zero)
      {
      sprintf(res_int+strlen(res_int), "%d", 0);
      }

    //將小數陣列轉成字串
    for(int i = 0;i < d_arr_index;i++)
    {
      sprintf(res_dec+strlen(res_dec), "%d", calc_dec_arr[i]);
      //std::cout << "calc_dec_arr:" << calc_dec_arr[i] << std::endl;
    }

    //std::cout << "integer:" << res_int << "\n";
    //std::cout << "decimal:" << res_dec << "\n";

    BigDecimal *r = new BigDecimal(res_int, res_dec);

    //std::cout << "Subtract done.\n";
    return r;
  }

  friend std::istream &operator>>(std::istream &in, BigDecimal *data)
  {
    char input[10000], buf[10000];
    in >> input;

    //此數為負數
    if(input[0] == '-')
    {
      //std::cout << "This is negative number\n";
      strcpy(buf, input+1);
      strcpy(input, buf);
      data->positive = false;
    }
    else
    {
      data->positive = true;
    }

    memset(data->ch_int_arr, 0, 10000);
    memset(data->ch_dec_arr, 0, 10000);

    //把整數與小數切割
    set_substr(input, data->ch_int_arr, data->ch_dec_arr);

    //std::cout << "int_arr"<<data->ch_int_arr << std::endl;
    //std::cout << "dec_arr"<<data->ch_dec_arr << std::endl;
    return in;
  }

  friend std::ostream &operator<<(std::ostream &out, BigDecimal *bigDecimal)
  {
    if(bigDecimal == NULL)
      return out;

    if(bigDecimal->positive == false && !check_all_zero(bigDecimal->ch_int_arr, bigDecimal->ch_dec_arr))
      std::cout << "-";
    if(strlen(bigDecimal->ch_dec_arr) == 1 && bigDecimal->ch_dec_arr[0] == '0')
      out << bigDecimal->ch_int_arr << ".0" << bigDecimal->ch_dec_arr << std::endl;
    else
      out << bigDecimal->ch_int_arr << "." << bigDecimal->ch_dec_arr << std::endl;

    return out;
  }

  static bool check_all_zero(char *int_arr, char *dec_arr)
  {
    for(int i = 0;i < strlen(int_arr);i++)
    {
      if(int_arr[i] != '0')
        return false;
    }

    for(int i = 0;i < strlen(dec_arr);i++)
    {
      if(dec_arr[i] != '0')
        return false;
    }

    return true;
  }

  private:
  char ch_int_arr[10000], ch_dec_arr[10000];
  bool positive = true;
};




int main()
{
  BigDecimal a, b;

  while(std::cin >> &a >> &b)
  {

    //std::cout << a + &b << std::endl;
    //std::cout << a - &b << std::endl;
    //std::cout << a * &b << std::endl;
    a ^ &b;
    //std::cout << a / &b << std::endl;
    //add(a_int, a_dec, b_int, b_dec);

    
  }
}