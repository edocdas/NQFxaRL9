#include<iostream>
#include<stack>

bool ischar(char input)
{
    return input == '(' || input == ')' || input == '[' || input == ']' || input == '{' || input == '}' ? true : false;
}

//越低的括號，優先順序越高
int precedence(char input)
{
    if(input == '(' || input == ')')
        return 0;
    else if(input == '[' || input == ']')
        return 1;
    else if(input == '{' || input == '}')
        return 2;
    
    return -1;
}

bool check_parenth(std::stack<char> *data, int *depth)
{
    std::stack<char> buf;
    int calc_depth = 0;
    while(!data->empty() || !buf.empty())
    {
        //右括號多於左括號
        if(data->empty() && !buf.empty())
        {
            return false;
        }
        //遇到右括號
        else if(data->top() == ')' || data->top() == ']' || data->top() == '}')
        {   
            //如果另一個stack為空，或者遇到順序更高或相同的
            if(buf.empty() || (precedence(data->top()) <= precedence(buf.top())))
            {
                buf.push(data->top());
                data->pop();
                calc_depth++;
                if(calc_depth > *depth)
                    *depth = calc_depth;
            }
            else
            {
                //std::cout << "data:" << precedence(data->top()) << std::endl;
                //std::cout << "buf:" << precedence(buf.top()) << std::endl;
                return false;
            }
        }
        //遇到左括號
        else if(data->top() == '(' || data->top() == '[' || data->top() == '{')
        {
            //buf沒有右括號比對
            if(buf.empty())
                return false;
            //兩者優先順序一樣
            else if(precedence(buf.top()) == precedence(data->top()))
            {
                //std::cout << "precedence equal\n";

                data->pop();
                buf.pop();
                calc_depth--;
            }
            else
                return false;
        }

        /*for (std::stack<char> dump = *data; !dump.empty(); dump.pop())
            std::cout << dump.top() << " ";
        std::cout << "\n";

        for (std::stack<char> dump = buf; !dump.empty(); dump.pop())
            std::cout << dump.top() << " ";
        std::cout << "\n";*/
    }
    return true;
}
/*
{[()]} -> true
([)] -> false
([]) -> false
(((()))) -> true
{[[(()]} -> false
)( -> false
( -> false
) -> false
({}) -> false
{{[[(())]]}} -> true
*/
int main()
{
    std::stack<char> data;
    std::string input;
    std::cout << "Please type your input\n";

    while(std::cin >> input)
    {

        std::stack<char> data;
        //放入需要比較的字元
        for(auto it = input.begin();it != input.end();it++)
        {
            if(ischar(*it))
                data.push(*it);
        }

        int depth = 0;
        //開始查核
        if(check_parenth(&data, &depth))
        {
            std::cout << "This string is balanced and properly nested\n";
            std::cout << "Maximum depth:" << depth << "\n";
        }
        else
            std::cout << "This string is not balanced or properly nested\n";
    }
}