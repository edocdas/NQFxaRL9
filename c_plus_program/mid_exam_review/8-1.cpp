//全對
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
    container(): box(nullptr), len(1) {}
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


class queue : private container
{
public:
  queue():container(){}
  queue(int l):container(l){}
  queue(const queue &a)
  {
    box = a.box;
    len = a.len;
    index = a.index;
  }

  bool enqueue(int data)
  {
    if(index+1 == len)
      return false;

    index++;
    box[index] = data;
    return true;
  }
  int *dequeue()
  {
    if(index == -1)
      return nullptr;

    int*ptr = new int;
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
  int getLen(){return len;}
private:
  int index = -1;
};
