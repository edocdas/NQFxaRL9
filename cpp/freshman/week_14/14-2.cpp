#include<string>
#include<iostream>


class Convert : public std::string
{
public:
  Convert() : std::string(){}
  Convert(const std::string& str) : std::string(str){}
  Convert(const std::string& str, size_t pos, size_t len = npos) : std::string(str, pos, len){}
  Convert(const char* s) : std::string(s){}
  Convert(const char* s, size_t n) : std::string(s, n){}
  Convert(size_t n, char c) : std::string(n, c){}
  template <class InputIterator>
  Convert(InputIterator first, InputIterator last) : std::string(first, last){}

  int toInt()
  {
    std::string to_int = *this;
    try
    {
      int convert_int = stoi(to_int);
      return convert_int;
    }
    catch (const std::invalid_argument& ia)
    {
      //std::cout << ia.what() << std::endl;
      //return 0;
    }
  }

  double toDouble()
  {
    std::string to_double = *this;
    try
    {
      double convert_double = stod(to_double);
      return convert_double;
    }
    catch (const std::invalid_argument& ia)
    {
      //std::cout << ia.what() << std::endl;
      //return 0;
    }
  }
};

int main()
{
  Convert a("123.45");
  std::string b = "123";
  //std::cout << a.stoi() << std::endl;
  //std::cout << stoi(b) << std::endl;
  std::cout << a.toInt() << std::endl;
  std::cout << a.toDouble() << std::endl;
}
