#include<iostream>
class container
{
private:
  int *box;
  int len;
  int index;
  static int count;
public:
  container(void): box(nullptr), len(0), index(-1) {increase();}
  container(int l){
    box = new int[l];
    len = l;
    index = -1;
    increase();
  }
  ~container()
  {
    decrease();
  }
  int getLen(){return len;}
  int getIndex(){return index;}
  bool reallocate(int size)
  {
    int *ptr = new int[size];
    if(!ptr)
      return false;

    for(int i = 0;i <= index;i++)
    {
      ptr[i] = box[i];
    }
    box = ptr;
    len = size;

    return true;
  }
  void traversal()
  {
    if(index == -1)
      std::cout << "empty\n";
    else
    {
      for(int i = 0;i <= index;i++)
      {
        std::cout << box[i] << " ";
      }
      std::cout << '\n';
    }
  }
  bool push(int value)
  {
    if(index+1 == len)
      if(!reallocate(len*2))
        return false;

    index++;
    box[index] = value;
    return true;
  }
  int pop()
  {
    if(index == -1)
      return 0;

    int num = box[0];
    for(int i = 0;i < index;i++)
      box[i] = box[i+1];
    index--;
    return num;
  }
  static void increase(){count++;}
  static void decrease(){count--;}
  static int getCount(){return count;}
};
int container::count = 0;


int main()
{
  container *ptr = new container, *ptr2 = new container;
  ptr->push(1);
  ptr->push(2);
  ptr->push(3);
  ptr->push(4);
  ptr->push(4);
  ptr->push(4);
  ptr->push(4);
  ptr->push(4);
  ptr->traversal();
  ptr->pop();
  ptr->traversal();
}
