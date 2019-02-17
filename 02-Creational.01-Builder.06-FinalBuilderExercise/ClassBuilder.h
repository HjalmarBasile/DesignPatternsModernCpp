#pragma once

#include "Class.h"

class ClassBuilder
{
	friend class Class;
public:
	ClassBuilder& withName(const std::string className)
	{
		m_Class.name = className;
		return *this;
	}

	ClassBuilder& addField(const std::string& name, const std::string& type)
	{
		m_Class.fields.emplace_back(Field(name, type));
		return *this;
	}

	operator Class() const { return std::move(m_Class); }
private:
	Class m_Class;

	ClassBuilder() {} /* Only Class can construct a ClassBuilder instance */
};
