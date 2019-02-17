#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

/*
 This is an example of a problem which should be solved using Factory Method pattern
*/
enum class PointType
{
	CARTESIAN,
	POLAR
};

struct Point
{
	/* Using a third parameter to solve the problem is not the best design */
	Point(float a, float b, PointType type = PointType::CARTESIAN)
	{
		if (type == PointType::CARTESIAN) {
			x = a;
			y = b;
		} else {
			x = a * cos(b);
			y = a * sin(b);
		}
	}

	float x, y;
};

int main()
{
	Point point1(0, 10, PointType::CARTESIAN);
	Point point2(10, M_PI_2, PointType::POLAR);

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
