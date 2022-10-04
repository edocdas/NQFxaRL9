//想法來源
//https://kt11273.pixnet.net/blog/post/217984822

#include<iostream>
#include<stack>
#include<cmath>

void move(std::stack<char> *stack_a, std::stack<char> *stack_b)
{
  //從A移動到B
  if(!stack_a->empty() && (stack_b->empty() || stack_a->top() > stack_b->top()))
  {
    stack_b->push(stack_a->top());
    stack_a->pop();

    return;
  }
  //從B移動到A
  else if(!stack_b->empty() && (stack_a->empty() || stack_b->top() > stack_a->top()))
  {
    stack_a->push(stack_b->top());
    stack_b->pop();

    return;
  }
}

template<class T>
void print(std::string str, std::stack<T> a)
{
  std::cout << str << " ";
  while(!a.empty())
  {
    std::cout << a.top() << " ";
    a.pop();
  }
  std::cout << "\n";
}

int main()
{
  std::stack<char> source, destination, auxiliary;
  int count = 0, step = 0;
  std::cin >> count;
  step = pow(2, count)-1;

  for(int i = 0;i < count;i++)
  {
    source.push('A'+i);
  }

  for(int i = 0;i < step;i++)
  {
    //奇數個碟子
    if(count % 2 == 1)
    {
      //std::cout << "hello\n";
      if(i % 3 == 0)
        move(&source, &destination);
      else if(i % 3 == 1)
        move(&source, &auxiliary);
      else if(i % 3 == 2)
        move(&auxiliary, &destination);
    }
    //偶數個碟子
    else
    {
      if(i % 3 == 0)
        move(&source, &auxiliary);
      else if(i % 3 == 1)
        move(&source, &destination);
      else if(i % 3 == 2)
        move(&auxiliary, &destination);
    }

    std::cout << "step:" << i+1 << std::endl;
    print("s:", source);
    print("a:", auxiliary);
    print("d:", destination);

  }
}