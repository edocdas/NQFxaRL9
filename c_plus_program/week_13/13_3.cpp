#include<iostream>
#include<climits>

class Container
{
public:
    Container()
    {
        index = 0;
    }
    void insert(int n)
    {
        if(n >= 0)
        {
            data[index] = n;
            index ++;
        }
    }
    virtual int remove() = 0;  //remove an element from container
    void display()
    {
        int j;
        if(index == 0)
            return;
        for(j = 0; j < index - 1; j ++)
            std::cout<<data[j]<<", ";
        std::cout<<data[j] << '\n';
    }
protected:
    int data[100];
    int index;
};

class RemoveFromBig : public Container
{
public:
  int remove()
  {
    if(index != 0)
    {
      int max = INT_MIN, record_index = 0;
      for(int i = 0;i < index;i++)
      {
        if(data[i] > max)
        {
          max = data[i];
          record_index = i;
        }
      }

      for(int i = record_index;i < index;i++)
      {
        data[i] = data[i+1];
      }
      index--;
      return max;
    }
    else
      return 0;
  }
};

class RemoveFromSmall : public Container
{
public:
  int remove()
  {
    if(index != 0)
    {
      int min = INT_MAX, record_index = 0;
      for(int i = 0;i < index;i++)
      {
        if(data[i] < min)
        {
          min = data[i];
          record_index = i;
        }
      }

      for(int i = record_index;i < index;i++)
      {
        data[i] = data[i+1];
      }
      index--;
      return min;
    }
    else
      return 0;
  }
};

int main()
{
  RemoveFromBig a;
  RemoveFromSmall b;


  a.insert(5);
  a.insert(2);
  a.insert(1);
  a.insert(4);
  a.insert(3);

  for(int i = 1;i <= 5;i++)
  {
    a.remove();
    a.display();
  }

  b.insert(5);
  b.insert(2);
  b.insert(1);
  b.insert(4);
  b.insert(3);

  for(int i = 1;i <= 5;i++)
  {
    b.remove();
    b.display();
  }
}
