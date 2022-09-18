#include<iostream>
#include<string>
#include<vector>

class Coordinate
{
public:
  Coordinate(){};
  Coordinate(int a, int b): x(a), y(b){}
	Coordinate(const Coordinate &it): x(it.x), y(it.y){}

	int getX() const{return x;}
	int getY() const{return y;}
	void setX(int val){x = val;}
	void setY(int val){y = val;}
	void showCoordInfo(){ std::cout << "(" << x << ", " << y << ")\n";}
  Coordinate& operator+(const Coordinate& second);
  Coordinate& operator-(const Coordinate& second);
  bool operator>(const Coordinate& second);
  bool operator<(const Coordinate& second);
  void operator=(const Coordinate& input){x = input.x, y = input.y;}
private:
  int x=0, y=0;
};
Coordinate& Coordinate::operator+(const Coordinate& second){
  Coordinate *buf = new Coordinate;
  buf->setX(this->getX() + second.getX());
  buf->setY(this->getY() + second.getY());
  return *buf;
}

Coordinate& Coordinate::operator-(const Coordinate& second){
  Coordinate *buf = new Coordinate;
  buf->setX(x - second.x);
  buf->setY(y - second.y);
  return *buf;
}

bool Coordinate::operator>(const Coordinate& second){
  int first_x = x, first_y = y;
  int second_x= second.x, second_y=second.y;
  return (first_x > second_x && first_y > second_y);
}

bool Coordinate::operator<(const Coordinate& second){
  int first_x = x, first_y = y;
  int second_x= second.x, second_y = second.y;
  return (first_x < second_x && first_y < second_y);
}
int main(){
  Coordinate a(1,2), b(3,4);
  Coordinate c = a + b;
  std::cout << (a > b) << " "<< (b > a) << "\n";
  std::cout << c.getX() << " "<< c.getY() << "\n";

}
