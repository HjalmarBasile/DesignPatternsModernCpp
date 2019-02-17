#pragma once

#include <string>
#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase
{
public:
	explicit PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

	PersonAddressBuilder& at(const std::string& streetAddress)
	{
		person.streetAddress = streetAddress;
		return *this;
	}

	PersonAddressBuilder& withPostCode(const std::string& postCode)
	{
		person.postCode = postCode;
		return *this;
	}

	PersonAddressBuilder& in(const std::string& city)
	{
		person.city = city;
		return *this;
	}

};
