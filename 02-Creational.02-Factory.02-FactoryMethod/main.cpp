#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

class Point
{
public:
	static Point CreateFromCartesianCoord(float x, float y) { return { x, y }; }
	static Point CreateFromPolarCoord(float rho, float theta) { return { rho * cos(theta), rho * sin(theta) }; }

private:
	Point(float x, float y) : x(x), y(y) {}
	float x, y;

	friend std::ostream& operator<<(std::ostream& os, const Point& point)
	{
		os << "Point(" << point.x << ", " << point.y << ")";
		return os;
	}
};

int main()
{
	Point point1 = Point::CreateFromCartesianCoord(0, 10);
	std::cout << point1 << std::endl;

	Point point2 = Point::CreateFromPolarCoord(10, (float)M_PI_2);
	std::cout << point2 << std::endl;

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
