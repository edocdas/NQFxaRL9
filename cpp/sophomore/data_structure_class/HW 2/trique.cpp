#include <iostream>
/*
使用circular queue實作trique
藉由保留一個位置，避免當全滿或全空，判斷條件一樣
以目前條件，兩個index相同時，為空

此資料結構大小由SIZE決定，此為static型態

*/
template <class T>
class trique
{
public:
    int Addrear(int data)
    {
        if(IsFull())
        {
            return -1;
        }
        else
        {
            std::cout << "Add rear:" << bot << std::endl;
            arr[bot] = data;
            bot = get_next_bot();
            return 1;
        }
    }

    int Addfront(int data)
    {
        if(IsFull())
        {
            return -1;
        }
        else
        {
            std::cout << "Add front:" << get_prev_top() << std::endl;
            arr[get_prev_top()] = data;
            top = get_prev_top();
            return 1;
        }
    }

    int AddMiddle(int data)
    {
        if(IsFull())
        {
            return -1;
        }
        else
        {
            int diff = top_to_bot_diff() / 2;
            //std::cout << "top_to_bot_diff:" << top_to_bot_diff() << std::endl;
            //std::cout << "diff:" << diff << std::endl;

            for(int iter = 0;iter < diff;iter++)
            {
                arr[get_prev(bot,iter)] = arr[get_prev(bot,iter+1)];

                if(iter + 1 == diff)
                    arr[get_prev(bot,iter+1)] = data;
            }
            bot = get_next_bot();
            return 1;
        }
    }

    T *DeleteFront()
    {
        if(IsEmpty())
            return NULL;
        else
        {
            T *num = new T(arr[top]);
            top = get_next_top();
            return num;
        };
    }

    T *DeleteRear()
    {
        if(IsEmpty())
            return NULL;
        else
        {
            T *num = new T(arr[get_prev_bot()]);
            bot = get_prev_bot();
            return num;
        };
    }

    T *DeleteMiddle()
    {
        if(IsEmpty())
            return NULL;
        else
        {
            int diff = top_to_bot_diff() / 2, del_index = top;

            for(int iter = 0;iter < diff;iter++)
            {
                del_index = (del_index + 1) % SIZE;
            }

            T *del_num = new T(arr[del_index]);
            bot = get_prev_bot();

            while(del_index != bot)
            {
                arr[del_index] = arr[(del_index+1) % SIZE];
                del_index = (del_index + 1) % SIZE;
            }

            return del_num;
        };
    }

    T CheckFront()
    {
        if(IsEmpty())
            return -1;

        return arr[top];
    }

    T CheckRear()
    {
        if(IsEmpty())
            return -1;

        return arr[get_prev_bot()];
    }

    T CheckMiddle()
    {
        if(IsEmpty())
            return -1;

        int diff = top_to_bot_diff() / 2, index = top;

        for(int iter = 0;iter < diff;iter++)
        {
            index = (index + 1) % SIZE;
        }

        return arr[index];
    }

    bool IsEmpty()
    {
        return bot == top;
    }

    bool IsFull()
    {
        return get_next_bot() == top;
    }

    int top_to_bot_diff()
    {
        int buf = top, diff = 0;
        while((buf+1) % SIZE != bot)
        {
            buf = (buf+1) % SIZE;
            diff++;
        }

        return diff+1;
    }

    void print()
    {
        int buf = top;
        while(buf != bot)
        {
            std::cout << arr[buf] << " ";
            buf = (buf+1) % SIZE;
        }
        std::cout << std::endl;
    }

    int get_prev_top() const
    {
        if(top-1 == -1)
            return SIZE-1;
        else
            return top-1;
    }

    int get_next_top() const
    {
        return (top+1) % SIZE;
    }

    int get_prev_bot() const
    {
        if(bot-1 == -1)
            return SIZE-1;
        else
            return bot-1;
    }

    int get_next_bot() const
    {
        return (bot+1) % SIZE;
    }

    int get_prev(int index, int time) const
    {
        for(int i = 0;i < time;i++)
        {
            if(index-1 == -1)
                index = SIZE-1;
            else
                index = index-1;
        }
        return index;
    }


private:
    static const int SIZE = 10;
    int arr[SIZE];
    int top = 0, bot = 0;
};


int main()
{
    trique <int> a;
    a.Addrear(1);
    a.print();
    a.Addfront(2);
    a.print();
    a.Addrear(3);
    a.print();
    a.Addfront(4);
    a.print();
    a.Addrear(6);
    a.print();


    a.AddMiddle(7);
    a.print();
    std::cout << a.CheckMiddle() << std::endl;
    a.AddMiddle(8);
    a.print();
    std::cout << a.CheckMiddle() << std::endl;
    a.AddMiddle(9);
    a.print();
    std::cout << a.CheckMiddle() << std::endl;
    a.AddMiddle(10);
    a.print();
    std::cout << a.CheckMiddle() << std::endl;

    a.DeleteMiddle();
    a.print();
    a.DeleteMiddle();
    a.print();
    a.DeleteMiddle();
    a.print();
    a.DeleteMiddle();
    a.print();


}