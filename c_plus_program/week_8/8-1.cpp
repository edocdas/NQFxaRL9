#include <iostream>

class container
{
protected:
    int *box;
    int len;
    void copy(int *from, int *to, int l)
    {
        for(int i=0; i<l; i++)
            to[i] = from[i];
    }
public:
    container(): box(NULL), len(1) {}
    container(int l)
    {
        int *tmp = new int[l];
        this->len = l;
        this->box = tmp;
    }
    container(const container &a)
    {
        int *tmp = new int[a.len];
        copy(a.box, tmp, a.len);
        this->len = a.len;
    }
    bool reallocate(int l)
    {
        int *tmp = new int[l];
        if(!tmp)
            return false;
        copy(this->box, tmp, this->len);
        delete box;
        this->box = tmp;
        this->len = l;
        return true;
    }
};

class queue : private container{
public:
  queue():index(-1), container(1){}
  queue(int l):index(-1), container(l){}
  queue(const queue &a)
  {
    int *tmp = new int[a.len];
    copy(a.box, tmp, a.len);
    this->len = a.len;
    this->box = tmp;
    this->index = a.index;
  }

  bool enqueue(int data);
  int *dequeue();
  int getLen() {return len;}
  bool increase();
  void traversal();

private:
  int index;
};

bool queue::enqueue(int data)
{
  if(index+1 == len)
    return false;
  else
  {
    box[index+1] = data;
    index++;
    return true;
  }
}

int* queue::dequeue()
{
  if(index == -1)
    return nullptr;
  else
  {
    int *ptr = new int;
    *ptr = box[0];
    for(int i = 0;i < index;i++)
    {
      box[i] = box[i+1];
    }
    index--;
    return ptr;
  }
}

bool queue::increase()
{
  if(reallocate(len*2))
    return true;
  else
    return false;
}

void queue::traversal(){
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

int main(){
  queue A;
  A.increase();
  std::cout << A.getLen() << std::endl;
  A.increase(); //變成四個位子
  std::cout << A.getLen() << std::endl;

  A.enqueue(1);
  A.enqueue(2);
  A.enqueue(3);
  A.enqueue(4);

  queue B(A);

  int *put_out;
  while(put_out = B.dequeue(), put_out != nullptr)
  {
    std::cout << "Put out:" << *put_out << "\n";
    B.traversal();
  }

  /*for(int i = 1;i <= 5;i++)
  {
    std::cout << "enqueue:" << i << " " <<A.enqueue(i) << std::endl;
    std::cout << "getlen:" << A.getLen() << std::endl;
  }

  while(put_out = A.dequeue(), put_out != nullptr)
  {
    std::cout << "Put out:" << *put_out << "\n";
    A.traversal();
  }*/
}
