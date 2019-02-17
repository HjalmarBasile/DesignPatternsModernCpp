#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

/*
 Having an inner factory is a better approach,
 since it is clear from the API of the Point class
 how to build a point instance.
*/
class Point
{
private:
	float x, y;
	Point(float x, float y) : x(x), y(y) {}

	class PointFactory
	{
	public:
		static Point CreateFromCartesianCoord(float x, float y) { return Point{ x, y }; }
		static Point CreateFromPolarCoord(float rho, float theta) { return Point{ rho * cos(theta), rho * sin(theta) }; }
	};

public:
	static PointFactory Factory;

	friend std::ostream& operator<<(std::ostream& os, const Point& point)
	{
		os << "Point(" << point.x << ", " << point.y << ")";
		return os;
	}
};

int main()
{
	Point point1 = Point::Factory.CreateFromCartesianCoord(0, 10);
	std::cout << point1 << std::endl;

	Point point2 = Point::Factory.CreateFromPolarCoord(10, (float)M_PI_2);
	std::cout << point2 << std::endl;

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
