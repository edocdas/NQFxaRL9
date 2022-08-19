#include<iostream>

template<typename T>
class Set
{
  public:

    Set():count(0){}
    Set(const Set &copy)
    {
      for(int i = 0;i < copy.count;i++)
      {
        element[i] = copy.element[i];
      }

      count = copy.count;
    }

    int add(const T input)
    {
      for(int i = 0;i < count;i++) //在set中找到了
      {
        if(element[i] == input)
          return 0;
      }

      //沒找到
      element[count] = input;
      count++;
      return 1;
    }

    int add(const Set input)
    {
      int add_number = 0;
      for(int i = 0;i < input.count;i++)
      {
        add_number += add(input.element[i]);
      }
      return add_number;
    }

  	void display()
    {
      int j;
      for(j = 0;j < count;j ++)
        std::cout<<element[j]<<" ";
    }
  private:
  	T element[100];
  	int count;
};

int main()
{
  Set<double> a, b;
  a.add(1.1);
  a.add(2.222);
  a.add(3.3);
  a.add(4);
  a.add(5);
  a.add(6);

  b.add(3);
  b.add(4);
  b.add(5);
  b.add(6);

  std::cout << a.add(7);
  b.display();
  a.display();
}
