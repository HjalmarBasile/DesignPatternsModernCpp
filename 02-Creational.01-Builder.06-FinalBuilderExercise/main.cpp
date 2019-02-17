#include <iostream>
#include "ClassBuilder.h"

int main()
{
	Class example = Class::make()
		.withName("Vector2D")
		.addField("x", "float")
		.addField("y", "float");

	std::cout << example << std::endl;

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
