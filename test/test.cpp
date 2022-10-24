#include<iostream>


int main()
{
    std::string a, b = "1";
    a.resize(10);
    while(a.length() < 20)
    {
        a += std::to_string(3);
        std::cout << a << std::endl;
    }
    std::cout << a.capacity() << std::endl;

    /*char input2[10000] = "12345";
    strcpy(input2+strlen(input2), "6");
    std::cout << input2 << std::endl;*/
}