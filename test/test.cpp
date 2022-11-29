#include<iostream>


int main()
{
    std::string children, data, path, type;
    std::string tree;

    std::getline(std::cin, tree);

    int type_index = tree.rfind("\"type\":"), path_index = tree.rfind("\"path\"");
    type = tree.substr(type_index+8);
    type = type.substr(0, type.length()-2);

    path = tree.substr(path_index+8, type_index-3-(path_index+7));

    if(tree.find("\"children\"") == 1)
    {
        children = tree.substr(12,path_index-1-12);
    }
    else if(tree.find("\"data\"") == 1)
    {
        data = tree.substr(9,path_index-2-9);
    }

    std::cout << "Children:" << children << std::endl;
    std::cout << "Data:" << data << std::endl;
    std::cout << "Path:" << path << std::endl;
    std::cout << "Type:" << type << std::endl;
}