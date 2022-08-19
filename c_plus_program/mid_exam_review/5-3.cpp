class Point
{
public:
	float x, y;
  bool operator ==(Point b) //記得寫多載
  {
    return x == b.x && y == b.y ? true : false;
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
  double x0 = c.x, y0 = c.y;
  double x1 = a.x, y1 = a.y;
  double x2 = b.x, y2 = b.y;

  return abs((x2-x1)*(y1-y0)-(x1-x0)*(y2-y1))/sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}
bool Triangle::isTriangle(Segment a, Segment b, Segment c)
{
  if(a.getPointA() == b.getPointA() && b.getPointB() == c.getPointB() && c.getPointA() == a.getPointB())
    return true;
  else if(a.getPointA() == b.getPointB() && b.getPointA() == c.getPointB() && c.getPointA() == a.getPointB())
    return true;
  else if(a.getPointA() == b.getPointA() && b.getPointB() == c.getPointA() && c.getPointB() == a.getPointB())
    return true;
  else if(a.getPointA() == b.getPointB() && b.getPointA() == c.getPointA() && c.getPointB() == a.getPointB())
    return true;

  if(a.getPointB() == b.getPointA() && b.getPointB() == c.getPointB() && c.getPointA() == a.getPointA())
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
  double f = seg1.getLength(), se = seg2.getLength(), t = seg3.getLength();
  double s = (f+se+t)/2;
  return sqrt(s*(s-f)*(s-se)*(s-t));
}
