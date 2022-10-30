#include<iostream>
#include<climits>
#include<sstream>

#define SIZE 100

/*
1,2,3,4,5,6
1,2,3

1,2,3,4
2,3,4,5

1,2,3,4
1,2,3,4

1,2,3
1,2,3,4,5,6
*/

void print(int *input, int count)
{
    for(int i = 0;i < count;i++)
    {
        if(input[i] != INT_MIN)
            std::cout << input[i] << " ";
    }
    std::cout << "\n";
}

bool check_left_element(int *input, int count)
{
    bool left = false;
    for(int i = 0;i < count;i++)
    {
        if(input[i] != INT_MIN)
            left = true;
    }
    
    return left;
}

int compareStringWordBags(std::string bag_a, std::string bag_b)
{
    std::string buf;
    int bag_a_arr[SIZE], bag_b_arr[SIZE], a_index = 0, b_index = 0;
    std::stringstream stream_a(bag_a), stream_b(bag_b);

    while(std::getline(stream_a, buf, ','))
    {
        bag_a_arr[a_index] = stoi(buf);
        a_index++;
    }

    while(std::getline(stream_b, buf, ','))
    {
        bag_b_arr[b_index] = stoi(buf);
        b_index++;
    }

    for(int i = 0;i < a_index;i++)
    {
        for(int j = 0;j < b_index;j++)
        {
            if(bag_a_arr[i] == bag_b_arr[j] && bag_a_arr[i] != INT_MIN)
            {
                bag_a_arr[i] = INT_MIN;
                bag_b_arr[j] = INT_MIN;
            }
        }
    }

    bool is_left_a_exist = check_left_element(bag_a_arr, a_index);
    bool is_left_b_exist = check_left_element(bag_b_arr, b_index);

    if(is_left_a_exist && is_left_b_exist)
        return INT_MAX;
    else if(!is_left_a_exist && !is_left_b_exist)
        return 0;
    else if(is_left_a_exist && !is_left_b_exist)
        return 1;
    else if(!is_left_a_exist && is_left_b_exist)
        return -1;
}

int main()
{
    std::string bag_a, bag_b;
    std::cout << "Please type two bag.\nex.1,2,3,4,5,6\n";
    while(std::cin >> bag_a >> bag_b)
    {
        int condiction = compareStringWordBags(bag_a, bag_b);

        if(condiction == -1)
            std::cout << "First bag is a proper subbag.\n";
        else if(condiction == 0)
            std::cout << "Two bags are equivalent.\n";
        else if(condiction == 1)
            std::cout << "First bag is a proper superbag.\n";
        else if(condiction == INT_MAX)
            std::cout << "Two bags are incomparable.\n";
    }
}