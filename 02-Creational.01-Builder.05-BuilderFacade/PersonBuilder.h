#pragma once

#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
public:
	PersonAddressBuilder lives() const;
	PersonJobBuilder works() const;

	/* Conversion operator */
	operator Person() const { return std::move(person); }

protected:
	PersonBuilderBase(Person& person) : person(person) {}
	Person& person;
};

class PersonBuilder : public PersonBuilderBase
{
	friend class Person;
private:
	PersonBuilder() : PersonBuilderBase(person) {}
	Person person;
};
