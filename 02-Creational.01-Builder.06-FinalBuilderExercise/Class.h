#pragma once

#include <ostream>
#include <string>
#include <vector>

class ClassBuilder;

class Field
{
	friend class ClassBuilder;
private:
	Field(const std::string& name, const std::string& type) : name(name), type(type) {}

	const std::string name;
	const std::string type;

	friend std::ostream& operator<<(std::ostream& os, const Field& field)
	{
		os << field.type << " " << field.name << ";";
		return os;
	}
};

class Class
{
	friend class ClassBuilder;
public:
	static ClassBuilder make();

private:
	std::string name;
	std::vector<Field> fields;

	friend std::ostream& operator<<(std::ostream& os, const Class& obj)
	{
		os << "class " << obj.name << "\n";
		os << "{\n";
		for (const auto& field : obj.fields) {
			os << "  " << field << "\n";
		}
		os << "};";
		return os;
	}
};
