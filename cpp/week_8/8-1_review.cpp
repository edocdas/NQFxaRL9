class queue : private container
{
public:
  queue():container(){}
  queue(int l):container(l){}
  queue(const queue&a)
  {
    box = a.box;
    len = a.len;
  }

  bool enqueue(int data)
  {
    if(index+1 == len)
      return false;

    index++;
    box[index] = data;
    return true;
  }

  int* dequeue()
  {
    if(index==-1)
      return nullptr;

    int* ptr = new int;
    *ptr = box[0];
    for(int i = 0;i < index;i++)
    {
      box[i] = box[i+1];
    }
    index--;
    return ptr;
  }

  bool increase()
  {
    if(reallocate(len*2))
      return true;
    else
      return false;
  }

  int getLen()
  {
    return len;
  }

private:
  int index=-1;
};

int main()
{
  
}
