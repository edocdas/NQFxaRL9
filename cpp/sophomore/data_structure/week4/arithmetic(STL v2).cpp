#include<cmath>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<stack>

//(-100)-((-10)*10))
//0.1+0.035+8*2(-
//((((-8)(/3)*0.5))^10
//-0.1+0.035+8*2


//EOF的問題
//https://latedev.wordpress.com/2012/12/04/all-about-eof/


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
double banker_rounding(const double input)
{
  //std::cout << "input:" << input << std::endl;

  bool isDecimal = false, isNegative = false;
  int bonus = 0;
  char ch[128], *dot_place = 0;
  sprintf(ch, "%lf", input);

  if(input - (long long int)input != 0 && (dot_place = strchr(ch, '.')) != NULL)
    isDecimal = true;

  if(input < 0)
    isNegative = true;
  
  if(isDecimal)
  {
    for(int i = strlen(ch)-1; ch[i-2] != '.';i--)
    {
      if(ch[i] - '0' > 5 || (ch[i] - '0' == 5 && (ch[i-1] - '0') % 2 == 1))
      {
        ch[i] = '0';
        check_9(ch, i-1, &bonus);
      }
    }


    *(dot_place + 3) = '\0';
    if(isNegative)
    {
      //std::cout << "negative:" << atof(ch) - bonus << std::endl;
      return atof(ch) - bonus;
    }
    else
    {
      //std::cout << "positive:" << atof(ch) + bonus << std::endl;
      return atof(ch) + bonus;
    }
  }

  //std::cout << "integer:" << input << std::endl;
  return input;
}

int percedence(char ch)
{
  if(ch == '^')
    return 0;
  else if(ch == '*' || ch == '/')
    return 1;
  else if(ch == '+' || ch == '-')
    return 2;
  else if(ch == '(')
    return 3;

  return -1;
}

bool check_symbol(char ch)
{
  char table[] = {'+','-','*','/','^','(',')'};
  for(int i = 0;i < 7;i++)
  {
    if(ch == table[i])
      return true;
  }
  
  return false;
}

double calculation(char ch, double a, double b)
{
  switch(ch)
  {
    case '+':
      return b+a;
    case '-':
      return b-a;
    case '*':
      return b*a;
    case '/':
      return b/a;
    case '^':
      return pow(b,a);
    default:
      return 0;
  }
}

class arithmetic{
  public:
  void convert_var()
  {

    //變數array，使用ASCII當作index
    int base_index = 'A';
    char *start = input, *end = input;
    
    //使用strtod尋找字串中的小數，如果該字元非小數，則繼續迭代
    while(*start != '\0')
    {
       if(!isdigit(*start))
        start++;
       else
       {
        //找到數字
        double r = strtod(start, &end);
        //定義變數
        char index[2] = {(char)base_index ,'\0'};
        //以此變數作為index放入數字
        var_array[base_index] = r;

        //複製字串
        strcpy(buf, end);
        strcpy(start, index);
        strcpy(start+1, buf);
        base_index++;

        //std::cout << "Step 1:" << input << std::endl;
       };
    }
  }


  bool infix_to_postfix()
  {
    try
    {
      std::stack<char> sym_stack;
      for(int i = 0;i < strlen(input);i++)
      {

        //如果是變數，就放到post_fix array
        if(input[i] >= 'A' && input[i] != '^')
        {
          //std::cout << "var\n";
          char ch_buf[2] = {input[i], '\0'};
          strcpy(postfix + strlen(postfix), ch_buf);
        }
        //需要先處裡負號的情況(前方為符號，且後方為變數，或者這個負號在最前方)
        else if(input[i] == '-' && input[i+1] != '\0' &&(i == 0 || (check_symbol(input[i-1]) && !check_symbol(input[i+1]) )))
        {
          //std::cout << "minus\n";
          var_array[input[i+1]] = var_array[input[i+1]] * -1;
        }
        //正常狀況，把符號放入(符號為左括號，或者stack為空，或者此符號比stack頂部符號)
        else if(input[i] != ')' && (sym_stack.empty() || input[i] == '(' || percedence(input[i]) < percedence(sym_stack.top())
          || sym_stack.top() == '^' && input[i] == '^'))
        {
          //std::cout << "push\n";
          sym_stack.push(input[i]);
        }
        //遇到右括號
        else if(input[i] == ')')
        {
          //std::cout << "right parenthesis\n";
          while(sym_stack.empty() || sym_stack.top() != '(')
          {
            if(sym_stack.empty())
            {
              throw -1;
            }
              
            char ch_buf[2] = {sym_stack.top(), '\0'};
            strcpy(postfix + strlen(postfix), ch_buf);
            sym_stack.pop();
          }

          //左括號拿掉
          sym_stack.pop();
        }
        //遇到順序比較低的運算子
        else
        {
          //拿符號直到stack為空，或者順序比stack符號小
          while(!sym_stack.empty() && percedence(input[i]) >= percedence(sym_stack.top()))
          {
            char ch_buf[2] = {sym_stack.top(), '\0'};
            strcpy(postfix + strlen(postfix), ch_buf);
            sym_stack.pop();
          }
          sym_stack.push(input[i]);
        }

        //print("for stack", sym_stack);
        //std::cout << postfix << std::endl;
      }

      //把剩下的符號拿出
      while(!sym_stack.empty())
      {
        char ch_buf[2] = {sym_stack.top(), '\0'};
        strcpy(postfix + strlen(postfix), ch_buf);
        sym_stack.pop();
      }

    //print("final stack", sym_stack);
    //std::cout << postfix << std::endl;
    }
    catch(int error_code)
    {
      if(error_code == -1)
      {
        std::cout << "ERROR\n";
        memset(postfix, 0, 10000);
        return 0;
      }
    }

    return 1;
  }

  bool calc()
  {
    try
    {
      std::stack<double> calc;
      for(int i = 0;i < strlen(postfix);i++)
      {
        if(postfix[i] == '(')
          throw -1;
        else if(!check_symbol(postfix[i]))
          calc.push(var_array[postfix[i]]);
        else
        {
          double var_a = 0, var_b = 0;

          if(calc.empty())
            throw -1;
          else
          {
            var_a = calc.top();
            calc.pop();
          }
          
          if(calc.empty())
            throw -1;
          else
          {
            var_b = calc.top();
            calc.pop();
          }

          double result = calculation(postfix[i], var_a, var_b);
          result = banker_rounding(result);
          calc.push(result);
        }

        //std::cout << postfix[i] << std::endl;
        //print("calc stack", calc);
      }
      std::cout << std::fixed << std::setprecision(2) << calc.top() << std::endl;

      memset(postfix, 0, 10000);
    }
    catch(int error_code)
    {
      if(error_code == -1)
      {
        std::cout << "ERROR\n";
        memset(postfix, 0, 10000);
        return 0;
      }
    }
    return 1;
  }

  bool read_input()
  {
    //ver 1. work
    std::cin >> input;
    return std::cin.eof();

    //ver 2. not work
    /*while(std::cin >> input)
    {
      return 0;
    }
    return 1;*/


    //ver 3. work
    /*while(std::cin >> input)
    {
      //1.把全部的數字轉成變數
      convert_var();
    
      //2.把infix轉成postfix
      if(!infix_to_postfix())
        continue;

      //3.開始計算，並得出結果
      if(!calc())
        continue;
    }*/
  }

  private:
  double var_array[128] = {0};
  char input[10000], buf[10000], postfix[10000];
  private:
};

int main()
{
  
  int is_eof = 0;
  arithmetic item;
  //item.read_input();
  
  //每一行運算式
  while(!is_eof)
  {
    is_eof = item.read_input();

    //1.把全部的數字轉成變數
    item.convert_var();
    
    //2.把infix轉成postfix
    if(!item.infix_to_postfix())
      continue;

    //3.開始計算，並得出結果
    if(!item.calc())
      continue;
  }
}