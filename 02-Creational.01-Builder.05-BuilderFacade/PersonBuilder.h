#pragma once

#include "Person.h"

class PersonSpecificationBuilderBase;
class PersonAddressBuilder;
class PersonJobBuilder;

class PersonReferenceHolder
{
public:
	/* Conversion operator */
	operator Person() const { return std::move(person); }
protected:
	PersonReferenceHolder(Person& person) : person(person) {}
	Person& person;
};

class PersonBuilderBase : public PersonReferenceHolder
{
	friend class PersonSpecificationBuilderBase;
public:
	PersonAddressBuilder lives() const;
	PersonJobBuilder works() const;

protected:
	PersonBuilderBase(Person& person) : PersonReferenceHolder(person) {}
};

class PersonSpecificationBuilderBase : public PersonReferenceHolder
{
public:
	PersonBuilderBase end() { return PersonBuilderBase(person); }

protected:
	PersonSpecificationBuilderBase(Person& person) : PersonReferenceHolder(person) {}
};

class PersonBuilder : public PersonBuilderBase
{
	friend class Person;
private:
	PersonBuilder() : PersonBuilderBase(person) {}
	Person person;
};
