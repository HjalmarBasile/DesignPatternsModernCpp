#include <iostream>
#include <string>
#include <sstream>
#include <vector>

struct HtmlElement
{
	const size_t indent_size = 2;
	std::string name;
	std::string text;
	std::vector<HtmlElement> elements;

	HtmlElement() {}
	HtmlElement(const std::string& name, const std::string& text)
		: name(name), text(text) {}

	std::string str(int indent = 0) const
	{
		std::ostringstream ssout;
		std::string ind(indent_size * indent, ' ');
		ssout << ind << "<" << name << ">" << std::endl;
		if (text.size() > 0) {
			ssout << std::string(indent_size * (indent + 1), ' ') << text << std::endl;
		}

		for (const auto& el : elements) {
			ssout << el.str(indent + 1);
		}

		ssout << ind << "</" << name << ">" << std::endl;
		return ssout.str();
	}
};

struct HtmlBuilder
{
	HtmlElement root;

	HtmlBuilder(const std::string& rootName)
	{
		root.name = rootName;
	}

	void addChild(const std::string& childName, const std::string& childText)
	{
		root.elements.emplace_back(HtmlElement(childName, childText));
	}

	std::string str() const { return root.str(); }
};

int main()
{
	HtmlBuilder builder{ "ul" };
	builder.addChild("li", "hello");
	builder.addChild("li", "world");
	std::cout << builder.str() << std::endl;

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
