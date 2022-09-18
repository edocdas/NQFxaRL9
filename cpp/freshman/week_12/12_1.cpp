#include <iostream>
#include <string>

//<a>Content goes here...</a>
class HTMLElement
{
public:
  HTMLElement(std::string input)
  {
    
    auto start = input.begin(), end = input.end();
    while(*start != '>')
      start++;
    tagName = input.substr(1,start-input.begin()-1);

    while(*end != '<')
      end--;
    content = input.substr(start-input.begin()+1, end-start-1);
  }
  std::string getTagName()
  {
    return tagName;
  }
  std::string getContent()
  {
    return content;
  }
private:
  std::string tagName, content;
};
int main() {
  std::string str;
  getline(std::cin,str);
  HTMLElement html(str);
  std::cout<<html.getTagName()<<std::endl;
  std::cout<<html.getContent()<<std::endl;
  return 0;
}
