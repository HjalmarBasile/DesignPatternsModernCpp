#pragma once

#include <string>
#include "PersonBuilder.h"

class PersonJobBuilder : public PersonSpecificationBuilderBase
{
public:
	PersonJobBuilder(Person& person) : PersonSpecificationBuilderBase(person) {}

	PersonJobBuilder& at(const std::string& companyName)
	{
		person.companyName = companyName;
		return *this;
	}

	PersonJobBuilder& as(const std::string& position)
	{
		person.position = position;
		return *this;
	}

};
