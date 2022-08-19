#include <iostream>
void dot();

int main(){
	dot();
  return 0;
}

void dot()
{
  char a;
  std::cin >> a;
  if(a == '.')
    return;
  else
    dot();

    std::cout << a;
}
