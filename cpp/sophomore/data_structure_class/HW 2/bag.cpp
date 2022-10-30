#include<iostream>
#include<climits>

/*
5 8 7 6 5 4
3 8 8 7
*/

class bag
{
    public:
        void read_in()
        {
            std::cout << "input a_count and numbers\n";
            std::cin >> a_count;
            if(a_count >= SIZE)
                std::cout << "Sorry, size is not enough.\n";
            else
            {
                for(int i = 0;i < a_count;i++)
                    std::cin >> data_a[i];
            }
            
            std::cout << "input b_count and numbers\n";
            std::cin >> b_count;
            if(a_count >= SIZE)
                std::cout << "Sorry, size is not enough.\n";
            else
            {
                for(int i = 0;i < b_count;i++)
                    std::cin >> data_b[i];
            }
        }

        //
        void bagInclusion() const
        {
            int incul_size = a_count > b_count ? a_count : b_count, incul_index = 0;
            int inclusion[incul_size], copy_a[a_count], copy_b[b_count];
            copy_array(copy_a, data_a, a_count);
            copy_array(copy_b, data_b, b_count);

            for(int i = 0;i < a_count;i++)
            {
                for(int j = 0;j < b_count;j++)
                {
                    if(copy_a[i] == copy_b[j] && copy_a[i] != INT_MIN)
                    {
                        inclusion[incul_index] = copy_a[i];
                        incul_index++;
                        copy_a[i] = INT_MIN;
                        copy_b[j] = INT_MIN;
                    }
                }
            }
            
            sort(inclusion, incul_index);
            std::cout << "Inclusion: ";
            for(int i = 0;i < incul_index;i++)
                std::cout << inclusion[i] << " ";
            std::cout << std::endl;
        }

        void bagUnion() const
        {
            int incul_size = a_count > b_count ? a_count : b_count, incul_index = 0;
            int union_arr[incul_size], copy_a[a_count], copy_b[b_count];
            copy_array(copy_a, data_a, a_count);
            copy_array(copy_b, data_b, b_count);

            for(int i = 0;i < a_count;i++)
            {
                for(int j = 0;j < b_count;j++)
                {
                    if(copy_a[i] == copy_b[j] && copy_a[i] != INT_MIN)
                    {
                        union_arr[incul_index] = copy_a[i];
                        incul_index++;
                        copy_a[i] = INT_MIN;
                        copy_b[j] = INT_MIN;
                    }
                }
            }

            for(int i = 0;i < a_count;i++)
            {
                if(copy_a[i] != INT_MIN)
                {
                    union_arr[incul_index] = copy_a[i];
                    incul_index++;
                }
            }

            for(int i = 0;i < b_count;i++)
            {
                if(copy_b[i] != INT_MIN)
                {
                    union_arr[incul_index] = copy_b[i];
                    incul_index++;
                }
            }

            sort(union_arr, incul_index);
            std::cout << "Union: ";
            for(int i = 0;i < incul_index;i++)
                std::cout << union_arr[i] << " ";
            std::cout << std::endl;
        }

        void bagSum() const
        {
            int sum_arr[a_count+b_count], sum_index = 0;
            for(int i = 0;i < a_count;i++)
            {
                sum_arr[sum_index] = data_a[i];
                sum_index++;
            }

            for(int i = 0;i < b_count;i++)
            {
                sum_arr[sum_index] = data_b[i];
                sum_index++;
            }

            sort(sum_arr, sum_index);
            std::cout << "Sum: ";
            for(int i = 0;i < sum_index;i++)
                std::cout << sum_arr[i] << " ";
            std::cout << std::endl;
        }

        void bagDifference() const
        {
            int copy_a[a_count], copy_b[b_count];
            copy_array(copy_a, data_a, a_count);
            copy_array(copy_b, data_b, b_count);

            for(int i = 0;i < a_count;i++)
            {
                for(int j = 0;j < b_count;j++)
                {
                    if(copy_a[i] == copy_b[j] && copy_a[i] != INT_MIN)
                    {
                        copy_a[i] = INT_MIN;
                        copy_b[j] = INT_MIN;
                    }
                }
            }
            
            sort(copy_a, a_count);
            std::cout << "Diffenence: ";
            for(int i = 0;i < a_count;i++)
            {
                if(copy_a[i] != INT_MIN)
                    std::cout << copy_a[i] << " ";

            }
            std::cout << std::endl;
        }

        void print(int *input, int count) const
        {
            for(int i = 0;i < count;i++)
            {
                if(input[i] != INT_MIN)
                    std::cout << input[i] << " ";
                std::cout << "\n";
            }
        }

        void copy_array(int *des, const int *source, int count) const
        {
            for(int i = 0;i < count;i++)
            {
                des[i] = source[i];
            }
        }

        void sort(int *input, int count) const
        {
            for(int i = 0;i < count;i++)
            {
                for(int j = i;j < count;j++)
                {
                    if(input[i] > input[j])
                    {
                        int buf = input[i];
                        input[i] = input[j];
                        input[j] = buf;
                    }
                }
            }
        }

    private:
    static const int SIZE = 100;
    int data_a[SIZE], a_count = 0;
    int data_b[SIZE], b_count = 0;
};

int main()
{
    bag a;
    a.read_in();
    a.bagInclusion();
    a.bagUnion();
    a.bagSum();
    a.bagDifference();
}