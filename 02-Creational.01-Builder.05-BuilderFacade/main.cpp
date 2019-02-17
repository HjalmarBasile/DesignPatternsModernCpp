#include <iostream>

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

int main()
{
	Person p = Person::make()
		.lives()
			.at("Street 123")
			.withPostCode("123456")
			.in("NYC")
			.end()
		.works()
			.at("ThatCompany")
			.as("Dev")
			.end();
	std::cout << p << std::endl;

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
