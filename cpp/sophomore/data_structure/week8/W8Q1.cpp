#include <asm-generic/errno.h>
#include<iostream>
#include<sstream>
#include<climits>
#include<cstring>

#define SIZE 10000

/**
 * A Node class of Doublely Linked List class
 */
template<class T>
class Node {
  public:

  /**
   * Construct a new Node object with no parameter
   */
  Node() {}

  /**
   * Construct a new Node object with parameter
   * @param data: data to put in
   */
  Node(T data)
  {
    this->data = data;
  }

  /**
   * Construct a new Node object with parameters
   * @param data: data to put in
   * @param prev: pointer to the previous node
   * @param next: pointer to the next node
   */
  Node(T data, Node<T> *prev, Node<T> *next)
  {
    this->prev = prev;
    this->next = next;
    this->data = data;
  }

  //更改成新的tail
  void setTail(Node<T> *new_tail)
  {
    next = new_tail;
  }

  //更改成新的head
  void setHead(Node<T> *new_head)
  {
    prev = new_head;
  }

  //回傳下一個node
  Node<T>* getNext()
  {
    return next;
  }

  //回傳下一個node
  Node<T>* getPrev()
  {
    return prev;
  }

  //回傳node裡的資料
  T getData()
  {
    return data;
  }

  private: 
    Node<T> *prev = nullptr;
    Node<T> *next = nullptr;
    T data;
};

/**
 * A Doublely Linked List class
 */
template<class T>
class LinkedList {
  public:

  /**
   * Construct a new LinkedList object with no parameter
   */
  LinkedList() {}

  /**
   * Add a node to the tail of the linked list
   * @param data: data to put in
   */
  void addToTail(T data)
  {
    if(tail == nullptr)
    {
    tail = new Node<T>(data);
    head = tail;
    }
    else {
      Node<T> *new_tail = new Node<T>(data);
      tail->setTail(new_tail);
      new_tail->setHead(tail);
      tail = new_tail;
    }
  }

  /**
   * Add a node to the head of the linked list
   * @param data: data to put in
   */
  void addToHead(T data)
  {
    if(head == nullptr)
    {
    head = new Node<T>(data);
    tail = head;
    }
    else {
      Node<T> *new_head = new Node<T>(data);
      head->setHead(new_head);
      new_head->setTail(head);
      head = new_head;
    }
  }

  /**
   * Delete a node from the linked list with the given data from the head
   * If there are no data to be deleted, then do nothing
   * @param data: data to delete
   */
  void deleteData(T data)
  {
    Node<T> *iter = head;
    while(iter != nullptr)
    {
      if(iter->getData() == data)
      {
        //更新node
        if(iter->getPrev() != nullptr)
          iter->getPrev()->setTail(iter->getNext());
        if(iter->getNext() != nullptr)
          iter->getNext()->setHead(iter->getPrev());

        //更新head & tail
        if(iter == head)
        {
          head = iter->getNext();
        }
        if(iter == tail)
        {
          tail = iter->getPrev();
        }
        
        delete iter;

        //任務完成
        return;
      }
      else
      {
        iter = iter -> getNext();
      }
    }
  }

  /**
   * Delete valid n nodes from the linked list with the given data from the head
   * If there are no more data to be deleted, then just skip
   * @param data: data to delete
   * @param n: max number of nodes to delete
   */
  void deleteData(T data, int n)
  {
    for(int i = 0;i < n;i++)
    {
      deleteData(data);
    }
  }

  T getfront()
  {
    return head->getData();
  }

  T getend()
  {
    return tail->getData();
  }

  bool isEmpty()
  {
    return head == nullptr ? true : false;
  }

  /**
   * Overload the operator << to print out all the data in the linked list from the head
   * There is a \n in the end of each print
   * 
   * Output example: 
   * If your linked list data is 5, 4, 3, 2, 1
   * then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
   */
  friend std::ostream &operator<<(std::ostream &out, LinkedList * n)
  {
    Node<T> *iter = n->head;
    int counter = 0;
    out << "(";
    while(iter != nullptr)
    {
      if(counter != 0)
        out << ", ";
      
      out << iter->getData();
      iter = iter->getNext();

      counter++;
    }
    out << ")\n";

    return out;
  }

  private: 
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
};

template<class T>
class Queue
{
  public:

  /**
   * Construct a new Queue object with no parameter
   */
  Queue()
  {
    list = new LinkedList<T>;
  }

  /**
   * Add a data to queue
   * @param data: data to be added to queue
   */
  void enqueue(T data)
  {
    list->addToTail(data);
  }

  /**
   * Remove a data from queue and return it
   * @return the data removed from queue
   */
  T dequeue()
  {
    T buf = list->getfront();
    list->deleteData(buf);
    return buf;
  }

  /**
   * @return the first element in the queue
   */
  T front()
  {
    return list->getfront();
  }

  /**
   * @return true if queue is empty, false otherwise
   */
  bool isEmpty()
  {
    return list->isEmpty();
  }

  friend std::ostream &operator<<(std::ostream &out, Queue * n)
  {
    out << n->list;

    return out;
  }

  private: 
    LinkedList<T> *list = nullptr;
};


class BigDecimal
{
  public:
  template<class T> friend class BinarySearchTree;
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
  BigDecimal(std::string input)
  {
    if(input[0] == '-')
    {
      std::string sub_str = input.substr(1);
      set_substr(&sub_str, &this->ch_int_arr, &this->ch_dec_arr);
      this->positive = false;
    }
    else
      set_substr(&input, &this->ch_int_arr, &this->ch_dec_arr);
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

    for(int i = 0;i <= a->ch_int_arr.length();i++)
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

    for(int i = 0;i <= a->ch_dec_arr.length();i++)
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
      if(*a_int >= *b_int)
        return true;
      else
        return false;
    }
  }

  bool equal(std::string *a_int, std::string *b_int) const
  {
    if(a_int->length() > b_int->length())
      return false;
    else if(a_int->length() < b_int->length())
      return false;
    else
    {
      for(int i = 0;i < a_int->length();i++)
      {
        //std::cout << a_int[i] << " " << b_int[i] << std::endl;

        if(a_int[i] != b_int[i])
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
  static void banker_rounding(BigDecimal *input)
  {

    std::string *a = &input->ch_int_arr, *b = &input->ch_dec_arr;

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
    i_arr[dot_place-ch] = '\0';
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

  void operator+=(const BigDecimal *input)
  {
    BigDecimal *buf = *this + input;

    this->ch_dec_arr = buf->ch_dec_arr;
    this->ch_int_arr = buf->ch_int_arr;
    this->positive = buf->positive;

    delete buf;
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

  void operator -=(const BigDecimal *input)
  {
    BigDecimal *buf = *this - input;

    this->ch_dec_arr = buf->ch_dec_arr;
    this->ch_int_arr = buf->ch_int_arr;
    this->positive = buf->positive;

    delete buf;
  }


  //把小數轉為整數，並記錄兩個數字的位數
  //可以先把每個位數相乘，之後再處理進位
  //(index從小到大放置數字)
  //直到最後，再把小數位放回
  //可能為零，小於一，或大於一

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
  
  void operator *=(const BigDecimal *input)
  {
    BigDecimal *buf = *this * input;

    this->ch_dec_arr = buf->ch_dec_arr;
    this->ch_int_arr = buf->ch_int_arr;
    this->positive = buf->positive;

    delete buf;
  }

  /*
  1.將小數改成整數，再開始進行除法
  （順便把前面的零拿掉）
  2.處理整數部分
  藉由使用迭代器，找到目前的比較數
  之後再拿除數與此比較數比較
  如果比較大，就用小一倍的數相減
  減完後，放回被除數
  並更新迭代器
  3.處理小數部分
  主要與整數部分做法相同
  差別在於，我們需要增加被除數的零
  （使用迭代器需要注意字串是否resize，如果有就需要更新迭代器）
  */
  BigDecimal* operator/(const BigDecimal *input)
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
          BigDecimal *multi_res = multi_a * &multi_b;
          //額外加一份，用作比大小
          *multi_res += &multi_a;

          //std::cout << "multiply num:" << multi_res->ch_int_arr << std::endl;

          //除數的乘積大於所選定的被除數
          if(bigger_integer(&multi_res->ch_int_arr, &buf2) && !((multi_res->ch_int_arr) == buf2))
          {
            //把比大小的額外一倍減掉
            *multi_res -= &multi_a;

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

            delete multi_res;
            delete after_sub;

            //std::cout << "input_a:" << input_a << std::endl;

            //放置數到商中
            res_int += std::to_string(i);

            while(*start == '0' && start != end)
              start++;

            end++;

            break;
          }
          delete multi_res;
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
          BigDecimal *multi_res = multi_a * &multi_b;
          //額外加一份，用作比大小
          *multi_res += &multi_a;

          //std::cout << "multiply num:" << multi_res->ch_int_arr << std::endl;

          //除數的乘積大於所選定的被除數
          if(bigger_integer(&multi_res->ch_int_arr, &buf2) && !((multi_res->ch_int_arr) == buf2))
          {
            //把比大小的額外一倍減掉
            *multi_res -= &multi_a;

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
            delete multi_res;
            delete after_sub;

            //放置數到商中
            res_dec += std::to_string(i);

            while(*start == '0' && start != end)
              start++;

            end++;

            break;
          }

          delete multi_res;
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

  void operator /=(const BigDecimal *input)
  {
    BigDecimal *buf = *this / input;

    this->ch_dec_arr = buf->ch_dec_arr;
    this->ch_int_arr = buf->ch_int_arr;
    this->positive = buf->positive;

    delete buf;
  }

  /*
  將指數次方的整數與小數分開
  整數直接用乘的
  小數則分成lna 與 e^x 計算
  */
  BigDecimal* operator^(const BigDecimal *input) const
  {
    BigDecimal *input_special;
    BigDecimal num_1("1","0"), num_2("2","0");
    //此數為1^b，且b為整數
    //std::cout << this->ch_int_arr << std::endl;
    //std::cout << this->ch_dec_arr << std::endl;
    //std::cout << input->ch_dec_arr << std::endl;
    if(this->ch_int_arr == "1" && (this->ch_dec_arr == "0" || this->ch_dec_arr == "00") && (input->ch_dec_arr == "0" || input->ch_dec_arr == "00"))
    {
      //std::cout << "1^b\n";
      //std::cout << (input->ch_int_arr[input->ch_int_arr.length()-1] - '0') % 2 << std::endl;
      //b為奇數
      if((input->ch_int_arr[input->ch_int_arr.length()-1] - '0') % 2 == 1)
      {
        if(this->positive == true)
        {
          input_special = new BigDecimal("1","0");
          return input_special;
        }
        else
        {
          input_special = new BigDecimal("1","0");
          input_special->positive = false;
          return input_special;
        }
      }
      //b為偶數
      else if((input->ch_int_arr[input->ch_int_arr.length()-1] - '0') % 2 == 0)
      {
        input_special = new BigDecimal("1","0");
        return input_special;
      }
    }
    //此數為a^0，且a為正數
    if(input->ch_int_arr == "0" && (input->ch_dec_arr == "0" || input->ch_dec_arr == "00") && input->positive == true)
    {
      input_special = new BigDecimal("1","0");
      return input_special;
    }
    //此數為a^0，且a為負數
    else if(input->ch_int_arr == "0" && (input->ch_dec_arr == "0" || input->ch_dec_arr == "00") && input->positive == false)
    {
      input_special = new BigDecimal("1","0");
      BigDecimal *buf_6 = num_1 / input_special;
      delete input_special;
      input_special = buf_6;
      return input_special;
    }

   
    BigDecimal *int_res = new BigDecimal("1","0"), *iter = new BigDecimal("0","0");

    //整數指數
    if(input->ch_int_arr != "0")
    {
      do
      {
        //乘以本身
        *int_res *= this;

        //加一
        *iter += &num_1;
        //std::cout << iter->ch_int_arr << std::endl;
        //std::cout << int_res->ch_int_arr << "." << int_res->ch_dec_arr << std::endl;

      }while(!(input->ch_int_arr == iter->ch_int_arr));

    }
    //std::cout << "integer pow complete\n";

    BigDecimal ln_calc(this->ch_int_arr,this->ch_dec_arr);
    BigDecimal *buf_1 = ln_calc - &num_1, *buf_2 = ln_calc + &num_1;
    BigDecimal *ln_numerator = *buf_1 / buf_2, *pow_ln_numerator = *ln_numerator * &num_1;
    BigDecimal *ln_denominator = new BigDecimal("1","0");
    
    BigDecimal *ln_result = new BigDecimal("0","0");

    //std::cout << "calc ln:\n";
    //計算ln(目前計算3000次，看準不準確)
    for(int round = 0;round < 3000;round++)
    {
      if(round != 0)
      {
        for(int pow_2 = 0 ; pow_2 < 2;pow_2++)
        {
          //std::cout << "\nstart\n";
          *pow_ln_numerator *= ln_numerator;
          //std::cout << "\nend\n";
          //std::cout << "pow_ln_numerator:" << pow_ln_numerator->ch_int_arr << "." << pow_ln_numerator->ch_dec_arr << std::endl;
        }

        *ln_denominator += &num_2;
      }

      BigDecimal *buf_3 = *pow_ln_numerator / ln_denominator;
      *ln_result += buf_3;

      delete buf_3;
      
      //std::cout << "integer:" << result->ch_int_arr << std::endl;
      //std::cout << "dec:" << result->ch_dec_arr << std::endl;
    }

    *ln_result *= &num_2;
    //std::cout << "integer:" << ln_result->ch_int_arr << std::endl;
    //std::cout << "dec:" << ln_result->ch_dec_arr << std::endl;
    
    delete buf_1;
    delete buf_2;
    delete ln_numerator;
    delete pow_ln_numerator;
    delete ln_denominator;



    BigDecimal input_dec("0", input->ch_dec_arr);
    BigDecimal *e_power = *ln_result * &input_dec;

    BigDecimal *counter = new BigDecimal("100","0");
    BigDecimal *result = new BigDecimal("1","0");

    for(int round = 100;round > 0;round--)
    {
      //std::cout << "round:" << round << std::endl;
      BigDecimal *buf_4 = *e_power * result;
      delete result;
      *buf_4 /= counter;

      result = *buf_4 + &num_1;
      delete buf_4;

      *counter -= &num_1;
    }

    //for (i = n - 1, sum = 1; i > 0; --i )
    //  sum = 1 + x * sum / i; 
    delete e_power;
    delete counter;
    delete ln_result;
    
    BigDecimal *final_res = *result * int_res;
    //std::cout << "final result:" << final_res->ch_int_arr << "." << final_res->ch_dec_arr << std::endl;

    delete result;
    delete int_res;
    delete iter;

    BigDecimal *buf_5;
    if(input->positive == false)
    {
      buf_5 = num_1 / final_res;
      delete final_res;
      final_res = buf_5;
    }

    return final_res;
  }


  //分成整數加法與小數加法
  //1.整數加法
  //(index從小到大)
  //2.小數加法
  //(index從大到小)
  //需要處理小數進位到整數的可能

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

    //std::cout << "a_i_arr:" << a_i_arr << " len:" << a_i_arr.length() << std::endl;
    //std::cout << "a_d_arr:" << a_d_arr << "len:" << a_d_arr.length() << std::endl;
    //std::cout << "b_i_arr:" << b_i_arr << "len:" << b_i_arr.length() << std::endl;
    //std::cout << "b_d_arr:" << b_d_arr << "len:" << b_d_arr.length() << std::endl;

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

  void opposite_sign()
  {
    if(this->positive == true)
      this->positive = false;
    else
      this->positive = true;
  }

  std::string get_num()
  {
    std::string return_num;
    if(this->positive == false && !check_all_zero(this->ch_int_arr, this->ch_dec_arr))
      return_num += "-";
    if(this->ch_dec_arr.length() == 1 && this->ch_dec_arr[0] == '0')
      return_num += this->ch_int_arr + ".0" + this->ch_dec_arr;
    else
      return_num += this->ch_int_arr + "." + this->ch_dec_arr;


    return return_num;
  }

  friend std::ostream &operator<<(std::ostream &out, BigDecimal *bigDecimal)
  {
    if(bigDecimal == NULL)
      return out;

    if(bigDecimal->positive == false && !check_all_zero(bigDecimal->ch_int_arr, bigDecimal->ch_dec_arr))
      std::cout << "-";
    if(bigDecimal->ch_dec_arr.length() == 1 && bigDecimal->ch_dec_arr[0] == '0')
      out << bigDecimal->ch_int_arr << ".0" << bigDecimal->ch_dec_arr;
    else
      out << bigDecimal->ch_int_arr << "." << bigDecimal->ch_dec_arr;

    return out;
  }

  

  private:
  std::string ch_int_arr, ch_dec_arr;
  bool positive = true;
};



template<class T> class BinarySearchTree;


/**
 * A TreeNode class of binarySearchTree class
 */
template<class T>
class TreeNode {
  public:
    friend class BinarySearchTree<T>;
    TreeNode(T input_data): data(input_data){}

  private:
    T data;
    TreeNode<T> *left = nullptr;
    TreeNode<T> *right = nullptr;
};

/**
 * A binarySearchTree abstract class for BinarySearchTree class
 */
template<class T>
class binarySearchTree {
  public:
    /**
     * Print preorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void preorder() = 0;

    /**
     * Print inorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void inorder() = 0;

    /**
     * Print postorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    virtual void postorder() = 0;

    /**
     * Print levelorder traversal of the tree
     * Format: "4,5,6,7". Data seperate by "," with no spaces between and without quotes
     */
    //virtual void levelorder() = 0;

    /**
     * Insert data into the tree if the value is not present
     * @param data data to insert
     * @return true if insert successfully, false if the value is already present
     */
    virtual bool insert(T data) = 0;

    /**
     * Set the value of the root
     * @param data to set to root
     */
    virtual void setRoot(T data) = 0;

    /**
     * Search the tree for the given value
     * @param target target to find
     * @return true if found, false if not found
     */
    virtual bool serach(T target) = 0;

    /**
     * Deserialize the string to a tree with levelorder traversal
     * @param tree to be deserialized
     */
    virtual void deSerialize(std::string tree) = 0;

    /**
     * Serialize the tree to a string with levelorder traversal
     * @return the serialized string
     */
    virtual std::string serialize() = 0;
  protected:
    TreeNode<T> *root;
};

template<class T>
class BinarySearchTree : public binarySearchTree<T> {
  public:
    void setRoot(T data)
    {
        this->root = new TreeNode<T>(data);
        //std::cout << "root:" << this->root->data << std::endl;
    }

    bool insert(T data)
    {
        TreeNode<T> *iter = this->root, *new_node = new TreeNode<T>(data);
        while(iter != nullptr)
        {
            //數字比目前node大
            if(stoi(data) > stoi(iter->data))
            {
                //std::cout << "Bigger than node\n";

                if(iter -> right != nullptr)
                    iter = iter->right;
                else
                    {
                        //std::cout << "Put right node\n";
                        iter->right = new_node;
                        return true;
                    }
            }
            //數字比目前node小
            else if(stoi(data) < stoi(iter->data))
            {
                //std::cout << "Smaller than node\n";

                if(iter -> left != nullptr)
                    iter = iter->left;
                else
                    {
                        //std::cout << "Put left node\n";
                        iter->left = new_node;
                        return true;
                    }
            }
            //數字與目前node相等
            else
            {
                //std::cout << "Equal node\n";
                delete new_node;
                return false;
            }
        }
    }

    bool serach(T target)
    {
        TreeNode<T> *iter = this->root;
        while(iter != nullptr)
        {
            //數字比目前node大
            if(stoi(target) > stoi(iter->data))
            {
                if(iter -> right != nullptr)
                    iter = iter->right;
                else
                    return false;
            }
            //數字比目前node小
            else if(stoi(target) < stoi(iter->data))
            {
                if(iter -> left != nullptr)
                    iter = iter->left;
                else
                    return false;
            }
            //數字與目前node相等
            else
            {
                return true;
            }
        }

        return false;
    }

    void preorder()
    {
        //std::cout << "Preorder\n";

        if(order_str.length() == 0)
            order_str += this->root->data;
        else
            order_str += "," + this->root->data;

        if(this->root->left != nullptr)
            preorder(this->root->left);
        if(this->root->right != nullptr)
            preorder(this->root->right);

        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void preorder(TreeNode<T> *cur_node)
    {
        if(order_str.length() == 0)
            order_str += cur_node->data;
        else
            order_str += "," + cur_node->data;

        if(cur_node->left != nullptr)
            preorder(cur_node->left);
        if(cur_node->right != nullptr)
            preorder(cur_node->right);
    }

    void inorder()
    {
        //std::cout << "Inorder\n";
        
        if(this->root->left != nullptr)
            inorder(this->root->left);

        if(order_str.length() == 0)
            order_str += this->root->data;
        else
            order_str += "," + this->root->data;

        if(this->root->right != nullptr)
            inorder(this->root->right);

        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void inorder(TreeNode<T> *cur_node)
    {
        if(cur_node->left != nullptr)
            inorder(cur_node->left);

        if(order_str.length() == 0)
            order_str += cur_node->data;
        else
            order_str += "," + cur_node->data;

        if(cur_node->right != nullptr)
            inorder(cur_node->right);
    }

    void postorder()
    {
         //std::cout << "Postorder\n";
        
        if(this->root->left != nullptr)
            postorder(this->root->left);

        if(this->root->right != nullptr)
            postorder(this->root->right);

        if(order_str.length() == 0)
            order_str += this->root->data;
        else
            order_str += "," + this->root->data;

        std::cout << order_str << std::endl;
        order_str.clear();
    }

    void postorder(TreeNode<T> *cur_node)
    {
        if(cur_node->left != nullptr)
            postorder(cur_node->left);
        if(cur_node->right != nullptr)
            postorder(cur_node->right);

        if(order_str.length() == 0)
            order_str += cur_node->data;
        else
            order_str += "," + cur_node->data;
    }

    void levelorder()
    {
        Queue<TreeNode<T>*> node;
        node.enqueue(this->root);

        while(!node.isEmpty())
        {
            TreeNode<T> *buf = node.front();
            node.dequeue();

            if(order_str.length() == 0)
                order_str += buf->data;
            else
                order_str += "," + buf->data;

            if(buf->left != nullptr)
                node.enqueue(buf->left);
            if(buf->right != nullptr)
                node.enqueue(buf->right);
        }

        //std::cout << "Levelorder\n";
        std::cout << order_str << std::endl;
        order_str.clear();
    }
    
    void deSerialize(std::string tree)
    {
      std::stringstream comma_split(tree);
      std::string sub_str;
      Queue<std::string> data_queue;
      Queue<TreeNode<T>*> next_queue;

      
      while(std::getline(comma_split, sub_str, ','))
      {
        if(sub_str == "NULL")
          data_queue.enqueue("NULL");
        else
          data_queue.enqueue(sub_str);
      }

      std::string buf;
      bool set_root = true;
      while(!data_queue.isEmpty())
      {
        TreeNode<T>* cur_node;

        //第一次放樹根
        if(set_root)
        {
          this->setRoot(data_queue.dequeue());
          set_root = false;

          cur_node = this->root;
          //std::cout << "root_node:" << cur_node->data << std::endl;
        }
        //之後的node
        else
        {
          cur_node = next_queue.dequeue();
          //std::cout << "cur_node:" << cur_node->data << std::endl;
        }

        //左node可放
        if(!data_queue.isEmpty() && (buf = data_queue.dequeue()) != "NULL")
        {
          cur_node->left = new TreeNode<T>(buf);
          next_queue.enqueue(cur_node->left);
          //std::cout << "left node place:" << cur_node->left->data << std::endl;
        }
        //右node可放
        if(!data_queue.isEmpty() && (buf = data_queue.dequeue()) != "NULL")
        {
          cur_node->right = new TreeNode<T>(buf);
          next_queue.enqueue(cur_node->right);
          //std::cout << "right node place:" << cur_node->right->data << std::endl;
        }
      }
    }


    std::string serialize()
    {
      Queue<TreeNode<T>*> node;
      node.enqueue(this->root);

      while(!node.isEmpty())
      {
          TreeNode<T> *buf = node.dequeue();
          if(buf == 0)
          {
            order_str += ",NULL";
          }
          else
          {
            if(order_str.length() == 0)
              order_str += buf->data;
            else
              order_str += "," + buf->data;

            node.enqueue(buf->left);

            node.enqueue(buf->right);
          }
      }

      std::string return_str = order_str;
      order_str.clear();

      //把多餘的,NULL刪掉
      while(return_str.find_last_not_of("NULL") == return_str.length()-5)
        return_str.resize(return_str.length()-5);
      return return_str;
    }

    bool isNumber(const std::string &input)
    {
      for(int i = 0;i < input.length();i++)
      {
        if(((input[i] == '-' && i == 0 && input.length() != 1) || (input[i] == '.' && i != 0) || 
        input[i] >= '0' && input[i] <= '9'))
          continue;
        else
          return false;
      }

      return true;
    }

    std::string expression_infix()
    {
      //root為數字，且左或右為非空
      if(isNumber(this->root->data) && (this->root->left != nullptr 
      || this->root->right != nullptr))
        return "ERROR";

      //直到root為數字就結束
      while(!isNumber(this->root->data))
      {
        TreeNode<T> *iter = find_calc();
        if(iter == nullptr)
          return "ERROR";
        else
        {
          BigDecimal a(iter->left->data), b(iter->right->data);
          //std::cout << "num_a:" << a.ch_int_arr << " " << a.ch_dec_arr << std::endl;
          //std::cout << "a_positive" << a.positive << std::endl;
          //std::cout << "num_b:" << b.ch_int_arr << " " << b.ch_dec_arr << std::endl;
          //std::cout << "b_positive" << b.positive << std::endl;
          BigDecimal *c = calculation(iter->data[0], &a, &b);
          c->banker_rounding(c);
          //std::cout << "num_c:" << c->ch_int_arr << " " << c->ch_dec_arr << std::endl;
          //std::cout << "c_positive" << c->positive << std::endl;
          iter->data = c->get_num();
          //std::cout << "iter->data:" << iter->data << std::endl;


          delete(iter->left);
          delete(iter->right);
          iter->left = 0;
          iter->right = 0;
        }

        //std::cout << "inorder:";
        //this->inorder();
      }

      return this->root->data;
    }

    BigDecimal* calculation(char ch, BigDecimal* a, BigDecimal* b)
    {
      switch(ch)
      {
        case '+':
          return *a + b;
        case '-':
          return *a - b;
        case '*':
          return *a * b;
        case '/':
          return *a / b;
        case '^':
          return *a ^ b;
        default:
          return 0;
      }
    }

    TreeNode<T>* find_calc()
    {

      //root為非數字，且左為數右為數
      if(!isNumber(this->root->data) && this->root->left && this->root->right 
      && isNumber(this->root->left->data) && isNumber(this->root->right->data))
      {
        //如果左的children與右的children都不存在（正常情形）
        if(this->root->left->left == nullptr && this->root->left->right == nullptr && 
        this->root->right->left == nullptr && this->root->right->right == nullptr)
          return this->root;
        else
          return 0;
      }
      //root為非數，且左或右為非數（代表需要再往下找）
      else if(!isNumber(this->root->data) && this->root->left && this->root->right 
      && (!isNumber(this->root->left->data) || !isNumber(this->root->right->data)))
      {
        if(!isNumber(this->root->left->data))
        {
          return find_calc(this->root->left);
        }
        if(!isNumber(this->root->right->data))
        {
          return find_calc(this->root->right);
        }
      }
      else
        return 0;
    }

    TreeNode<T>* find_calc(TreeNode<T>* iter)
    {
      if(!isNumber(iter->data) && iter->left && iter->right 
      && isNumber(iter->left->data) && isNumber(iter->right->data))
      {
        if(iter->left->left == nullptr && iter->left->right == nullptr && 
        iter->right->left == nullptr && iter->right->right == nullptr)
          return iter;
        else
          return 0;
      }
      else if(!isNumber(iter->data) && iter->left && iter->right 
      && (!isNumber(iter->left->data) || !isNumber(iter->right->data)))
      {
        if(!isNumber(iter->left->data))
          return find_calc(iter->left);
        if(!isNumber(iter->right->data))
          return find_calc(iter->right);
      }
      else
        return 0;
    }

private:
    std::string order_str;
};

#include <cstdio>

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  std::string line;
  while(std::getline(std::cin, line))
  {
    BinarySearchTree<std::string> tree;
    tree.deSerialize(line);
    
    //std::cout << "levelorder\n";
    //tree.levelorder();
    //std::cout << "inorder\n";
    //tree.inorder();

    std::cout << tree.expression_infix() << std::endl;
    line.clear();
    //std::cout << tree.serialize() << std::endl;
  }
}