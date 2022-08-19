//參考：https://en.wikipedia.org/wiki/Line–line_intersection#cite_note-GGIII-2
#include <cmath>
#include <iostream>

class Coordinate
{
public:
Coordinate(int a=0, int b=0) : x(a), y(b){
}
Coordinate(Coordinate &it) : x(it.x), y(it.y){
}

int getX(){
	return x;
}
int getY(){
	return y;
}
void setX(int val){
	x = val;
}
void setY(int val){
	y = val;
}
void showCoordInfo(){
	std::cout << "(" << x << ", " << y << ")\n";
}

private:
int x;
int y;
};

class Segment // using two Coordinate to represent a segment
{
public:
Segment(Coordinate input_a, Coordinate input_b)
   {
      a.setX(input_a.getX());
      a.setY(input_a.getY());

      b.setX(input_b.getX());
      b.setY(input_b.getY());
   }

// return the intersection with another segment if exist, return NULL when there are no intersection.
Coordinate *getIntersection(Segment s)
{
	double x1 = s.a.getX(), y1 = s.a.getY(), x2 = s.b.getX(), y2 = s.b.getY();
	double x3 = a.getX(), y3 = a.getY(), x4 = b.getX(), y4 = b.getY();

	double t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
	double u = ((x1-x3)*(y1-y2)-(y1-y3)*(x1-x2))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
	if(t >= 0 && t <= 1 && u >= 0 && u <= 1)
	{
		double sect_x = x1 + t*(x2-x1), sect_y = y1 + t*(y2-y1);

		Coordinate *item = new Coordinate;
		item->setX(sect_x);
		item->setY(sect_y);
		return item;
	}
	else
		return NULL;
}


float length() // return the length of segment
{
	return sqrt(pow(a.getX()-b.getX(),2)+pow(a.getY()-b.getY(),2));
}

private:
Coordinate a, b;
};

int main(){
	Coordinate a(0,0), b(1,0), c(1,0), d(2,0);
	Segment first(a,b), second(c,d);

	Coordinate *ptr = first.getIntersection(second);
	if(ptr != nullptr)
		ptr->showCoordInfo();
	else
		std::cout << "not intersect.\n";

	std::cout << first.length() << '\n';
	std::cout << second.length() << '\n';

}
