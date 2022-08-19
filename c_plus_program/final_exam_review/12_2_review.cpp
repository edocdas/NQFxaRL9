#include<string>
#include<map>
#include<list>
#include<iostream>

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

class HTMLElementWithAttributes : public HTMLElement
{
public:
  HTMLElementWithAttributes(std::string input):HTMLElement(input)
  {
    auto it = input.begin();
    while(*it != '>')
    {
      if(*it == '"')
      {
        auto name_begin = it, name_end = it-1;
        while(*name_begin != ' ') name_begin--;
        name_begin++;

        auto value_begin = it+1, value_end = value_begin;
        while(*value_end != '"') value_end++;

        std::string name = input.substr(name_begin-input.begin(), name_end-name_begin);
        std::string value = input.substr(value_begin-input.begin(), value_end-value_begin);
        attributes.insert(std::make_pair(name, value));

        //忘記加這行
        it = value_end+1;
      }
      else
        it++;
    }
  }

  std::list<std::string> getAttributes()
  {
    std::list<std::string> lis;
    auto lis_iter = lis.begin();
    for(auto it: attributes)
      lis.insert(lis_iter, it.first);

    return lis;
  }

  std::string operator[](std::string key)
  {
    auto it = attributes.find(key);
    if(it != attributes.end())
      return it -> second;
    else
      return "";
  }
private:
	std::map<std::string, std::string> attributes;
};
int main() {
  std::string str;
  std::getline(std::cin,str);
  HTMLElementWithAttributes html(str);
  std::cout << html.getTagName() << std::endl ;
  std::list<std::string> key = html.getAttributes();
  for(std::string k : key)
    std::cout<<html[k]<<std::endl;
  return 0;
}
