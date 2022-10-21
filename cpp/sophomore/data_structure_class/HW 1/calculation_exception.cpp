#include<iostream>

double calculation(double input_a, double input_b, char i_operator)
{
  try
  {
    switch(i_operator)
    {
      case '+':
        return input_a + input_b;
      case '-':
        return input_a - input_b;
      case '*':
        return input_a * input_b;
      case '/':
        if(input_b == 0)
          throw "Oops, looks like you divide zero...\n";
        else
          return input_a / input_b;
        break;
      default:
        throw i_operator;
    }
  }
  catch (char a)
  {
    std::cout << "invaild operator, check your input\n";
  }
  catch (char const *str)
  {
    std::cout << str;
  }

  return -1;
}

int main()
{
  double input_a = 0, input_b = 0;
  char i_operator;
  while(std::cin >> input_a >> i_operator >> input_b)
    std::cout << calculation(input_a, input_b, i_operator) << std::endl;
}