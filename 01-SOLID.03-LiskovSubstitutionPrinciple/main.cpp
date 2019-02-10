#include <iostream>

/*
 Liskov Substitution Principle: "Subtypes must be behaviorally substitutable for their base types"
*/

class Rectangle
{
public:
	Rectangle(int width, int height) : width(width), height(height) {}

	int GetWidth() { return this->width; }
	int GetHeight() { return this->height; }

	virtual void SetWidth(int width) { this->width = width; }
	virtual void SetHeight(int height) { this->height = height; }

	int area() { return width * height; }

protected:
	int width, height;
};

class Square : public Rectangle
{
public:
	Square(int size) : Rectangle(size, size) {}

	void SetWidth(int width) override { this->width = this->height = width; }
	void SetHeight(int height) override { this->width = this->height = height; }
};

/*
 This function violates the Liskov Substitution Principle:
 it should lead to the same expected behaviour for
 any rectangle object and any other object
 instance of a class which derives from Rectangle,
 but this is not the case for a square object.

 The root of the problem is that it is actually a bad idea
 to have Square inherit from Rectangle, they should be
 siblings instead.
*/
void process(Rectangle& rect)
{
	int w = rect.GetWidth();
	rect.SetHeight(10);

	std::cout << "Expected area = " << w * 10 << "\n";
	std::cout << "Actual area = " << rect.area() << "\n";
	std::cout << std::endl;
}

int main()
{
	Rectangle r(5, 5);
	process(r);

	Square s(5);
	process(s);

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
