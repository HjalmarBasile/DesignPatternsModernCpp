#pragma once

#include <string>
#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase
{
public:
	PersonJobBuilder(Person& person) : PersonBuilderBase(person) {}

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
