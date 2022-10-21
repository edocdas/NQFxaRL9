//預期為兩個正數減法(大減小)
  BigDecimal* sub(const char *a_i_arr, const char *a_d_arr, const char *b_i_arr, const char *b_d_arr)
  {
    BigDecimal b_9_complement(b_i_arr, b_d_arr);

    //有可能b的小數比少
    if(strlen(b_d_arr) < strlen(a_d_arr))
    {
      for(int i = 0;i < strlen(a_d_arr)-strlen(b_d_arr);i++)
        strcpy(b_9_complement.ch_dec_arr+strlen(b_9_complement.ch_dec_arr), "0\0");
    }

    //進行9補數
    nine_complement(b_9_complement.ch_int_arr, b_9_complement.ch_dec_arr);

    BigDecimal *res = add(a_i_arr, a_d_arr, b_9_complement.ch_int_arr, b_9_complement.ch_dec_arr), buf;
    
    //a的小數比b大(整數少一位，小數最小位數加一)
    if(bigger_dec(a_d_arr, b_d_arr))
    {
      char buf_arr[10000];
      memset(buf_arr, 0, 10000);

      for(int i = 0;i < strlen(res->ch_dec_arr);i++)
      {
        
        //最後一個放零
        if(i + 1 == strlen(res->ch_dec_arr))
        {
          strcpy(buf_arr+strlen(buf_arr), "1\0");
          break;
        }

        strcpy(buf_arr+strlen(buf_arr), "0\0");
      }

      //加上小數最小位數
      res = add(res->ch_int_arr, res->ch_dec_arr, "0", buf_arr);

      //最後把整數減去一位
      strcpy(res->ch_int_arr, res->ch_int_arr+1);
    }
    //a的小數比b小(小數9補數翻轉)
    else
    {
      for(int i = 0;i < strlen(res->ch_dec_arr);i++)
      {
        res->ch_dec_arr[i] = ('9' - res->ch_dec_arr[i]) + '0';
      }

      //最後把整數減去一位
      strcpy(res->ch_int_arr, res->ch_int_arr+1);
    }

    return res;
  }