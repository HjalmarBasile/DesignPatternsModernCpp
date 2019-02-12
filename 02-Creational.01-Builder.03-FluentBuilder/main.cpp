#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

class HtmlBuilder;

class HtmlElement
{
	friend class HtmlBuilder;
public:
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

	static std::unique_ptr<HtmlBuilder> make(const std::string& rootName)
	{
		return std::make_unique<HtmlBuilder>(rootName);
	}

private:
	const size_t indent_size = 2;
	std::string name;
	std::string text;
	std::vector<HtmlElement> elements;

	HtmlElement() {}
	HtmlElement(const std::string& name, const std::string& text)
		: name(name), text(text) {}
};

class HtmlBuilder
{
public:
	HtmlBuilder(const std::string& rootName)
	{
		root.name = rootName;
	}

	HtmlBuilder& addChild(const std::string& childName, const std::string& childText)
	{
		root.elements.emplace_back(HtmlElement(childName, childText));
		return *this;
	}

	HtmlElement build() const { return root; }

private:
	HtmlElement root;
};

int main()
{
	HtmlElement el = HtmlElement::make("ul")->addChild("li", "hello").addChild("li", "world").build();
	std::cout << el.str() << std::endl;

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
