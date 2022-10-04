//把infix轉為postfix
//https://raj457036.github.io/Simple-Tools/prefixAndPostfixConvertor.html

//想法
/*
1.把infix轉為postfix
2.運用stack運算postfix

testcase
10+(100*30+4)
10+20-30*40+(1230-1230)*0


*/
#include<stack>
#include<string>
#include<iostream>
#include<cmath>

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

int percedence(char ch)
{
  if(ch == '^')
    return 0;
  else if(ch == '*' || ch == '/')
    return 1;
  else if(ch == '+' || ch == '-')
    return 2;

  //右括號的情況
  return 3;
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
      std::cout << "輸入有錯誤喔\n";
      return 0;
  }
}

template<class T>
void print(std::stack<T> a)
{
  while(!a.empty())
  {
    std::cout << a.top() << " ";
    a.pop();
  }
  std::cout << "\n";
}

int main()
{
  std::stack<double> operand;
  std::stack<char> symbol;
  std::string str, postfix;
  std::cin >> str;
  str = "(" + str + ")";
  int symbol_index[10000] = {0}, symbol_count = 0, str_count = 0;

  //找到每個符號的index
  for(auto str_iter = str.cbegin(); str_iter != str.end(); str_iter++, str_count++)
  {
    if(check_symbol(*str_iter))
    {
      symbol_index[symbol_count] = str_count;
      symbol_count++;
    }
  }

  //把符號添加到stack，並轉成postfix
  for(int i = 0;i < symbol_count;i++)
  {
    //取得目前運算符號
    char cur_char = str[symbol_index[i]];
    //stack為空，或者上一個為左括號
    if(symbol.empty() || symbol.top() == '(' || cur_char == '(')
    {
      //std::cout << "must-put:" << cur_char << std::endl;
      symbol.push(cur_char);
    }
    //擁有更高優先序的運算元
    else if(percedence(cur_char) < percedence(symbol.top()))
    {
      //std::cout << "higher-percedence:" << cur_char << std::endl;
      symbol.push(cur_char);
    }
    //此運算元為右括號
    else if(cur_char == ')')
    {
      //std::cout << "right parenthesis:" << cur_char << std::endl;
      while(symbol.top() != '(')
      {
        double fir = operand.top(), sec = 0;
        operand.pop();
        sec = operand.top();
        operand.pop();
        char ch = symbol.top();
        symbol.pop();

        operand.push(calculation(ch, fir, sec));
      }

      //把左括號拿掉
      symbol.pop();
    }
    //擁有更低優先序的運算元
    else
    {
      //std::cout << "lower percednece:" << cur_char << std::endl;
      double fir = operand.top(), sec = 0;
      operand.pop();
      sec = operand.top();
      operand.pop();
      char ch = symbol.top();
      symbol.pop();

      operand.push(calculation(ch, fir, sec));
      symbol.push(cur_char);
    }


    //把數字放進去
    if(i+1 != symbol_count)
      if(str.substr(symbol_index[i]+1, symbol_index[i+1]-symbol_index[i]-1) != "")
        operand.push(stod(str.substr(symbol_index[i]+1, symbol_index[i+1]-symbol_index[i]-1)));
  

    //print(operand);
    //print(symbol);
  }

  std::cout << operand.top() << std::endl;
}