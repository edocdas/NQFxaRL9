#include<cmath>

class Point
{
public:
	float x, y;
	bool operator==(const Point B)
	{
		return x == B.x && y == B.y ? true : false;
	}
};

class Segment
{
public:
	Segment()
	{
	}
	Segment(Point _a, Point _b)
	{
		a = _a;
		b = _b;
	}
	Point getPointA()
	{
		return a;
	}
	Point getPointB()
	{
		return b;
	}
	void setPoint(Point _a, Point _b)
	{
		a = _a;
		b = _b;
	}
	float getLength()
	{
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	float getDistance(const Point &a);
private:
	Point a, b;
};

class Triangle
{
public:
	Triangle(Segment s1, Segment s2, Segment s3)
	{
		seg1 = s1;
		seg2 = s2;
		seg3 = s3;
	}
	static bool isTriangle(Segment , Segment , Segment );
	float getArea();

private:
	Segment seg1, seg2, seg3;
};
float Segment::getDistance(const Point &c)
{
	double result = abs((b.x-a.x)*(a.y-c.y)-(a.x-c.x)*(b.y-a.y))/sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
	return result;
}
bool Triangle::isTriangle(Segment a, Segment b, Segment c)
{
	if(a.getPointA()== b.getPointA() && b.getPointB() == c.getPointB() && c.getPointA() == a.getPointB())
		return true;
	else if(a.getPointA() == b.getPointB() && b.getPointA() == c.getPointB() && c.getPointA() == a.getPointB())
		return true;
	else if(a.getPointA() == b.getPointA() && b.getPointB() == c.getPointA() && c.getPointB() == a.getPointB())
		return true;
	else if(a.getPointA() == b.getPointB() && b.getPointA() == c.getPointA() && c.getPointB() == a.getPointB())
		return true;
	else if(a.getPointB() == b.getPointA() && b.getPointB() == c.getPointB() && c.getPointA() == a.getPointA())
		return true;
	else if(a.getPointB() == b.getPointB() && b.getPointA() == c.getPointB() && c.getPointA() == a.getPointA())
		return true;
	else if(a.getPointB() == b.getPointA() && b.getPointB() == c.getPointA() && c.getPointB() == a.getPointA())
		return true;
	else if(a.getPointB() == b.getPointB() && b.getPointA() == c.getPointA() && c.getPointB() == a.getPointA())
		return true;

	return false;
}
float Triangle::getArea()
{
	double seg1_length = seg1.getLength(), seg2_length = seg2.getLength(), seg3_length = seg3.getLength();
	double s = (seg1_length + seg2_length + seg3_length)/2;
	return sqrt(s*(s-seg1_length)*(s-seg2_length)*(s-seg3_length));
}
