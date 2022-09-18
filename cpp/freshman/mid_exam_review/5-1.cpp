//全對，因為昨天已經把全部細節釐清
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
  container(int l)
  {
    box = new int[l];
    len = l;
    index = -1;
    increase();
  }
  ~container()
  {
    decrease();
  }
  static void increase(){count++;}
  static void decrease(){count--;}
  static int getCount(){return count;}
  bool reallocate(int size)
  {
    int*ptr = new int[size];
    if(!ptr)
      return false;

    for(int i = 0;i <= index;i++)
    {
      ptr[i] = box[i];
    }
    len = size;
    ptr = box;
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

  bool push(int data)
  {
    if(index+1 == len)
      if(!reallocate(len*2))
        return false;

    index++;
    box[index] = data;
    return true;
  }

  int pop()
  {
    if(index == -1)
      return 0;

    int buf = box[0];
    for(int i = 0;i < index;i++)
    {
      box[i] = box[i+1];
    }
    index--;
    return buf;
  }
  int getLen(){return len;}
  int getIndex(){return index;}
};
int container::count = 0;
