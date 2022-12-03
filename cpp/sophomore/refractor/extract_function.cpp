#include<iostream>


void print_and_write(std::string &Input_String, std::string Write_String)
{
    auto print = [](std::string Input_String, int Print_Number)
    {
        std::cout << "str:" << Input_String << std::endl;
        std::cout << "num:" << Print_Number << std::endl;
    };

    auto write = [](std::string Write_String)
    {
        Write_String = "change";
    };
 
    
    int Print_Number = 1244;
    print(Input_String, Print_Number);
    write(Write_String);
}

int main()
{
    std::string a = "Hello", b = "rest";

    print_and_write(a,b);
    std::cout << a << std::endl;
}