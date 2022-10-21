#include<iostream>
#include<cstring>

int main()
{
    char input[10000] = "008810", buf[10000]="1894=15895782345789=14";
    while(input[0] == '0')
    {
        strcpy(buf, input+1);
        strcpy(input, buf);
        std::cout << input << std::endl;
    }

    /*char input2[10000] = "12345";
    strcpy(input2+strlen(input2), "6");
    std::cout << input2 << std::endl;*/
}