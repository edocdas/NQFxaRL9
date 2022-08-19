//新的問題，為什麼把內部new的東西刪除，會runtime error
//線與點的距離：https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
//兩個線段相交：https://en.wikipedia.org/wiki/Line–line_intersection#cite_note-GGIII-2
//三角形面積：https://en.wikipedia.org/wiki/Triangle#Using_coordinates


#include<cmath>
#include<iostream>

class Point
{
public:
	float x, y;
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
	Point getPointA() const
	{
		return a;
	}
	Point getPointB() const
	{
		return b;
	}
	void setPoint(Point _a, Point _b)
	{
		a = _a;
		b = _b;
	}
	float getLength() const
	{
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	float getDistance(Point c) const // the height from point to the line which segment lie on.
  {
    return (double)abs((b.x - a.x)*(a.y - c.y)-(a.x - c.x)*(b.y - a.y))
              /sqrt((pow(b.x - a.x,2)+pow(b.y - a.y,2)));
  }
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
	static bool isTriangle(Segment seg1, Segment seg2, Segment seg3)
        //to determine if three segment can construct a triangle. they must overlap at the endpoint to construct a triangle.
        {
          Point *sect_data[3]={nullptr}; //產生三個相交的點
          for(int i = 0;i < 3;i++)
          {
            double x1, y1, x2, y2, x3, y3, x4, y4;
            if(i == 0) //檢測線段1與線段2
            {
              x1 = seg1.getPointA().x, y1 = seg1.getPointA().y, x2 = seg1.getPointB().x, y2 = seg1.getPointB().y;
            	x3 = seg2.getPointA().x, y3 = seg2.getPointA().y, x4 = seg2.getPointB().x, y4 = seg2.getPointB().y;
            }
            else if(i == 1) //檢測線段2與線段3
            {
              x1 = seg2.getPointA().x, y1 = seg2.getPointA().y, x2 = seg2.getPointB().x, y2 = seg2.getPointB().y;
            	x3 = seg3.getPointA().x, y3 = seg3.getPointA().y, x4 = seg3.getPointB().x, y4 = seg3.getPointB().y;
            }
            else if(i == 2) //檢測線段3與線段1
            {
              x1 = seg3.getPointA().x, y1 = seg3.getPointA().y, x2 = seg3.getPointB().x, y2 = seg3.getPointB().y;
            	x3 = seg1.getPointA().x, y3 = seg1.getPointA().y, x4 = seg1.getPointB().x, y4 = seg1.getPointB().y;
            }

            double t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
          	double u = ((x1-x3)*(y1-y2)-(y1-y3)*(x1-x2))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
          	if(t >= 0 && t <= 1 && u >= 0 && u <= 1) //有相交
          	{
          		double sect_x = x1 + t*(x2-x1), sect_y = y1 + t*(y2-y1);

          		sect_data[i] = new Point;
          		sect_data[i]->x = sect_x;
          		sect_data[i]->y = sect_y;
            }
          }

          //如果沒有產生point，就代表沒有相交，不會產生三角形
          if(sect_data[0] == nullptr || sect_data[1] == nullptr || sect_data[2] == nullptr)
          {
            return false;
          }
          //三點皆相同，不會產生三角形
          else if(sect_data[0]->x == sect_data[1]->x && sect_data[1]->x == sect_data[2]->x
                  && sect_data[0]->y == sect_data[1]->y && sect_data[1]->y == sect_data[2]->y)
                  {
                    //std::cout << "three line intersect the same point\n";
                    return false;
                  }
          else //構成一個三角形
          {
            //std::cout << "They exist a area\n";
            return true;
          }
        }
	float getArea() //return the area of triangle
        {
            Point *sect_data[3]={nullptr};
            for(int i = 0;i < 3;i++)
            {
              double x1, y1, x2, y2, x3, y3, x4, y4;
              if(i == 0)
              {
                x1 = seg1.getPointA().x, y1 = seg1.getPointA().y, x2 = seg1.getPointB().x, y2 = seg1.getPointB().y;
              	x3 = seg2.getPointA().x, y3 = seg2.getPointA().y, x4 = seg2.getPointB().x, y4 = seg2.getPointB().y;
              }
              else if(i == 1)
              {
                x1 = seg2.getPointA().x, y1 = seg2.getPointA().y, x2 = seg2.getPointB().x, y2 = seg2.getPointB().y;
              	x3 = seg3.getPointA().x, y3 = seg3.getPointA().y, x4 = seg3.getPointB().x, y4 = seg3.getPointB().y;
              }
              else if(i == 2)
              {
                x1 = seg3.getPointA().x, y1 = seg3.getPointA().y, x2 = seg3.getPointB().x, y2 = seg3.getPointB().y;
              	x3 = seg1.getPointA().x, y3 = seg1.getPointA().y, x4 = seg1.getPointB().x, y4 = seg1.getPointB().y;
              }

              double t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
            	double u = ((x1-x3)*(y1-y2)-(y1-y3)*(x1-x2))/((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));
            	if(t >= 0 && t <= 1 && u >= 0 && u <= 1)
            	{
            		double sect_x = x1 + t*(x2-x1), sect_y = y1 + t*(y2-y1);

            		sect_data[i] = new Point;
            		sect_data[i]->x = sect_x;
            		sect_data[i]->y = sect_y;
              }
            }

            if(sect_data[0] == nullptr || sect_data[1] == nullptr || sect_data[2] == nullptr)
            {
              //std::cout << "two line are parallel\n";

              return 0.0;
            }
            else if(sect_data[0]->x == sect_data[1]->x && sect_data[1]->x == sect_data[2]->x
                    && sect_data[0]->y == sect_data[1]->y && sect_data[1]->y == sect_data[2]->y)
                    {
                      //std::cout << "three line intersect the same point\n";
                      return 0.0;
                    }
            else //上方都做與isTriangle一樣的事
            {
              //std::cout << "They exist a area\n";
              //std::cout << "Point 1:" << sect_data[0]->x << " "<< sect_data[0]->y << '\n';
              //std::cout << "Point 2:" << sect_data[1]->x << " "<< sect_data[1]->y << '\n';
              //std::cout << "Point 3:" << sect_data[2]->x << " "<< sect_data[2]->y << '\n';

              double result = (double)1/2 * abs((sect_data[0]->x-sect_data[2]->x)*(sect_data[1]->y-sect_data[0]->y)
                                  -(sect_data[0]->x-sect_data[1]->x)*(sect_data[2]->y-sect_data[0]->y));
              return result;

            }
        }
private:
	Segment seg1, seg2, seg3;
};

int main(){
  Point a11, a12, a21, a22, a31, a32, test;
  a11.x = 0, a11.y = 0;
  a12.x = 0, a12.y = 2;
  a21.x = 2, a21.y = 0;
  a22.x = 1, a22.y = 2;
  a31.x = 2, a31.y = 0;
  a32.x = 0, a32.y = 0;
  test.x = -4, test.y = 0;
  Segment a1(a11, a12), a2(a21, a22), a3(a31, a32);

  std::cout << a1.getDistance(test) << '\n';

  Triangle data(a1, a2 ,a3);

  std::cout << data.getArea() << '\n';
}
