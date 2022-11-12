#include<iostream>


int main()
{
    //int a = NULL;
    std::string test = "NULL";
    int a = 2, b = 0;
    a ? a += 1 : b += 1;
    std::cout << a << " " << b << std::endl;
    b ? a += 1 : b += 1;
    std::cout << a << " " << b << std::endl;


    /*char input2[10000] = "12345";
    strcpy(input2+strlen(input2), "6");
    std::cout << input2 << std::endl;*/
}