#include <iostream>
#include <string>
#include <map>
#include <list>

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

//example
//<a href="HELLo" test="Sleep" abba="cddc" asdf="helo">Visit W3Schools</a>


class HTMLElementWithAttributes : public HTMLElement
{
public:
  HTMLElementWithAttributes(std::string input):HTMLElement(input)
  {
    auto split_place = input.begin();
    while(*split_place != '>')
    {
      if(*split_place == '"') //找到前後的分裂點
      {
        auto key_begin = split_place, key_end = split_place-1;
        while(*key_begin != ' ') key_begin--; //找到key頭的前一個（目前為空白）
        key_begin++;

        auto value_begin = split_place+1, value_end = value_begin;
        while(*value_end != '"') value_end++; //找到value尾的最後一個

        std::string key = input.substr(key_begin-input.begin(),key_end-key_begin);
        std::string value = input.substr(value_begin-input.begin(),value_end-value_begin);
        attributes.insert(std::make_pair(key,value));

        split_place = value_end + 1;
      }
      else
        split_place++;
    }
  }

  std::list<std::string> getAttributes()
  {
    std::list<std::string> list_key;
    auto iter_list = list_key.begin();
    for(auto it = attributes.begin();it != attributes.end();it++)
      list_key.insert(iter_list, it->first);
    return list_key;
  }
  std::string operator[](std::string key)
  {
    auto iter = attributes.find(key);
    if(iter != attributes.end())
      return iter -> second;
    else
      return "";
  }

private:
  std::map<std::string, std::string> attributes;
};
int main() {
  std::string str;
  getline(std::cin,str);
  HTMLElementWithAttributes html(str);
  std::cout << html.getTagName() << std::endl ;
  std::list<std::string> key = html.getAttributes();

  for(std::string k : key)
    std::cout<<html[k]<<std::endl;
  return 0;
}
