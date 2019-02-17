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
		.works()
		.at("ThatCompany")
		.as("Dev");
	std::cout << p << std::endl;

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
