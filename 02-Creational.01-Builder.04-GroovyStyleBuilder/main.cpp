#include<iostream>
#include<string>
#include<vector>

class Tag
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
	{
		std::string ind1(Tag::indentStart, ' ');
		std::string ind2(Tag::indentStart + Tag::indentStep, ' ');
		os << ind1 << "<" << tag.name;

		for (const auto& [key, val] : tag.attributes) {
			os << " " << key << "=\"" << val << "\"";
		}

		if (tag.text.length() == 0 && tag.children.size() == 0) {
			os << "/>";
		} else {
			os << ">" << std::endl;
			if (tag.text.length() > 0) {
				os << ind2 << tag.text << std::endl;
			}

			Tag::indentStart += 2;
			for (const auto& child : tag.children) {
				os << child;
			}
			Tag::indentStart -= 2;

			os << ind1 << "</" << tag.name << ">";
		}

		os << std::endl;
		return os;
	}

protected:
	Tag(const std::string& name, const std::string& text)
		: name(name), text(text) {}

	Tag(const std::string& name, const std::vector<Tag>& children)
		: name(name), children(children) {}

	inline static unsigned int indentStart = 0;
	static constexpr unsigned int indentStep = 2;
	std::string name;
	std::string text;
	std::vector<Tag> children;
	std::vector<std::pair<std::string, std::string>> attributes;
};

class P : public Tag
{
public:
	explicit P(const std::string& text)
		: Tag("p", text) {}

	P(std::initializer_list<Tag> children)
		: Tag("p", children) {}
};

class IMG : public Tag
{
public:
	explicit IMG(const std::string& url)
		: Tag("img", "")
	{
		attributes.emplace_back(std::make_pair("src", url));
	}
};

int main()
{
	std::cout <<
	P {
		P("Hello"),
		IMG("https://example.com/mypic.png"),
		P("The End!")
	}
	<< std::endl;

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
