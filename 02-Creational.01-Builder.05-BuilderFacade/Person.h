#pragma once

#include <iostream>
#include <string>

class PersonBuilder;

class Person
{
	friend class PersonBuilder;
	friend class PersonAddressBuilder;
	friend class PersonJobBuilder;
public:
	static PersonBuilder make();
	~Person() { std::cout << "Person destroyed\n"; }

private:
	Person() { std::cout << "Person created\n"; }

	std::string streetAddress;
	std::string postCode;
	std::string city;
	std::string companyName;
	std::string position;

	friend std::ostream& operator<<(std::ostream& os, const Person& p)
	{
		os << "StreetAddress {"	<< p.streetAddress <<	"} ";
		os << "PostCode {"		<< p.postCode <<		"} ";
		os << "City {"			<< p.city <<			"} ";
		os << "CompanyName {"	<< p.companyName <<		"} ";
		os << "Position {"		<< p.position <<		"} ";
		return os;
	}

};
