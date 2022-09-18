#include<iostream>
#include<iomanip>

int main()
{
  void *data[10];

  int a = 123, b = 11;
  int *c = &a;

  data[0] = &a;
  data[1] = &c;

  std::cout << std::setw(10) << "a: " << &a << std::endl;
  std::cout << std::setw(10) << "data[0]: " << data[0] << std::endl;

  std::cout << std::setw(10) << "c: " << c << std::endl;
  std::cout << std::setw(10) << "&c: " << &c << std::endl;
  std::cout << std::setw(10) << "data[1]: " << data[1] << std::endl;

  int **d = (int**)data[1];

  std::cout << std::setw(10) << "data[1]: " << *d << std::endl;


  /*if(*((int*)data[1]) == (int*)data[0])
    std::cout << "equal\n";
  else
    std::cout << "not equal\n";*/
}
