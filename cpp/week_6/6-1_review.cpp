#include<iostream>

class Coordinate
{
public:
  Coordinate():x(0), y(0){}
  Coordinate(const Coordinate &a):x(a.x), y(a.y){}
  Coordinate(int input_x, int input_y): x(input_x), y(input_y){}
  int getX() const{return x;}
  int getY() const{return y;}
  void setX(int val);
  void setY(int val);
  void showCoordInfo() const{std::cout << "(" << x << ", " << y << ")\n";}
  Coordinate& operator +(const Coordinate input)
  {
    Coordinate *buf = new Coordinate;
    buf->x = this->x + input.x;
    buf->y = this->y + input.y;
    return *buf;
  }
  Coordinate& operator -(const Coordinate input)
  {
    Coordinate *buf = new Coordinate;
    buf->x = this->x - input.x;
    buf->y = this->y - input.y;
    return *buf;
  }
  bool operator >(const Coordinate input)
  {
    return (x > input.x) && (y > input.y) ? true : false;
  }
  bool operator <(const Coordinate input)
  {
    return (x < input.x) && (y < input.y) ? true : false;
  }
  bool operator ==(const Coordinate input)
  {
    return (x == input.x) && (y == input.y) ? true : false;
  }
private:
  int x, y;
};
int main()
{

}
