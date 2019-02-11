#include <iostream>
#include <string>
#include <vector>
#include <tuple>

/*
 Dependency Inversion Principle:
 A. High-level modules should not depend on low-level modules. Both should depend on abstractions.
 B. Abstractions should not depend on details. Details should depend on abstractions.
*/

enum class Relationship
{
	PARENT,
	CHILD,
	SIBLING
};

struct Person
{
	std::string name;
};

struct RelationshipsBadPractice /* low-level module */
{
	std::vector<std::tuple<Person, Relationship, Person>> relations;

	void addParentAndChild(const Person& parent, const Person& child)
	{
		relations.push_back( { parent, Relationship::PARENT, child} );
		relations.push_back( { child, Relationship::CHILD, parent } );
	}
};

/*
 This is bad because we are letting an high-level module
 depend on a low-level module. Any change in implementation
 of the low-level module would break the high-level module.
*/
struct ResearchBadPractice /* high-level module */
{
	std::vector<Person> findAllChildrenOf(const std::string& name, const RelationshipsBadPractice& relation)
	{
		std::vector<Person> res;
		for (const auto& [first, rel, second] : relation.relations) {
			if (first.name == name && rel == Relationship::PARENT) {
				res.push_back(second);
			}
		}
		return res;
	}
};

/*
 Let's introduce abstraction
*/
struct RelationshipBrowser
{
	virtual std::vector<Person> findAllChildrenOf(const std::string& name) = 0;
};

struct Relationships : RelationshipBrowser /* low-level module */
{
	std::vector<std::tuple<Person, Relationship, Person>> relations;

	void addParentAndChild(const Person& parent, const Person& child)
	{
		relations.push_back({ parent, Relationship::PARENT, child });
		relations.push_back({ child, Relationship::CHILD, parent });
	}

	std::vector<Person> findAllChildrenOf(const std::string& name) override
	{
		std::vector<Person> res;
		for (const auto& [first, rel, second] : relations) {
			if (first.name == name && rel == Relationship::PARENT) {
				res.push_back(second);
			}
		}
		return res;
	}
};

/*
 Now both high-level and low-level modules depend on abstraction
*/
struct Research /* high-level module */
{
	void research(RelationshipBrowser& browser)
	{
		for(const auto& child : browser.findAllChildrenOf("John")) 
		{
			std::cout << child.name << " is a child of John" << std::endl;
		}
	}
};

int main()
{
	Person parent{ "John" };
	Person child1{ "Chris" };
	Person child2{ "Matt" };

	Relationships relationships;
	relationships.addParentAndChild(parent, child1);
	relationships.addParentAndChild(parent, child2);

	Research r;
	r.research(relationships);

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
