#include<iostream>
#include<stack>

void move(std::stack<char> *stack_a, std::stack<char> *stack_b, char a_name, char b_name)
{
  //從A移動到B
  if(!stack_a->empty() && (stack_b->empty() || stack_a->top() < stack_b->top()))
  {
    std::cout << "Move disk " << stack_a->top() << " from peg " << a_name << " to peg " << b_name << std::endl;

    stack_b->push(stack_a->top());
    stack_a->pop();
    return;
  }
  //從B移動到A
  else if(!stack_b->empty() && (stack_a->empty() || stack_b->top() < stack_a->top()))
  {
    std::cout << "Move disk " << stack_b->top() << " from peg " << b_name << " to peg " << a_name << std::endl;

    stack_a->push(stack_b->top());
    stack_b->pop();

    return;
  }
}

template<class T>
void print(std::string str, std::stack<T> a)
{
  std::stack<T> buf;
  while(!a.empty())
  {
    buf.push(a.top());
    a.pop();
  }

  std::cout << str << " ";
  while(!buf.empty())
  {
    std::cout << buf.top() << " ";
    buf.pop();
  }
  std::cout << "\n";
}

void odd_t_o_h(int count, std::stack<char>* s, std::stack<char>* a, std::stack<char>* d)
{
  if(count % 3 == 0)
    move(s, d, 'A', 'C');
  else if(count % 3 == 1)
    move(s, a, 'A', 'B');
  else if(count % 3 == 2)
    move(a, d, 'B', 'C');


  std::cout << "round:" << count+1 << std::endl;
  print("A", *s);
  print("B", *a);
  print("C", *d);
  std::cout << "\n";

  if(s->empty() && a->empty())
    return;
  else
    odd_t_o_h(count+1, s, a, d);
}

void even_t_o_h(int count, std::stack<char>* s, std::stack<char>* a, std::stack<char>* d)
{
  if(count % 3 == 0)
    move(s, a, 'A', 'B');
  else if(count % 3 == 1)
    move(s, d, 'A', 'C');
  else if(count % 3 == 2)
    move(a, d, 'B', 'C');

  std::cout << "round:" << count+1 << std::endl;
  print("A", *s);
  print("B", *a);
  print("C", *d);
  std::cout << "\n";

  if(s->empty() && a->empty())
    return;
  else
    even_t_o_h(count+1, s, a, d);
}

int main()
{
  std::stack<char> source, destination, auxiliary;
  int count = 0;
  std::cin >> count;

  for(int i = count-1;i >= 0;i--)
  {
    source.push('1'+i);
  }

  if(count % 2 == 1)
    odd_t_o_h(0, &source, &auxiliary, &destination);
  else
    even_t_o_h(0, &source, &auxiliary, &destination);
}
