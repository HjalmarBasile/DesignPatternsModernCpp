#include <iostream>
#include <string>
#include <vector>

/*
 Open-Close principle:
 "Software entities should be open for extension, but closed for modification"
 i.e. extending functionalities should not come to the cost
 of modifying the whole codebase
*/

enum class Color { RED, GREEN, BLUE };
enum class Size { SMALL, MEDIUM, LARGE };

struct Product
{
	std::string name;
	Color color;
	Size size;
};

void PrintProducts(const std::vector<Product*>& products)
{
	for (const auto& product : products) {
		std::cout << product->name << " ";
	}
	std::cout << std::endl;
}

/*
 This implementation is not generic, if we added more enum types
 we would have to add new filters and combinations as well
*/
struct BadProductFilter
{
	typedef std::vector<Product*> Items;

	Items byColor(const Items& items, const Color color)
	{
		Items res;
		for (const auto& item : items) {
			if (color == item->color) {
				res.push_back(item);
			}
		}
		return res;
	}

	Items bySize(const Items& items, const Size size)
	{
		Items res;
		for (const auto& item : items) {
			if (size == item->size) {
				res.push_back(item);
			}
		}
		return res;
	}

	Items byColorAndSize(const Items& items, const Color color, const Size size)
	{
		Items res;
		for (const auto& item : items) {
			if (color == item->color && size == item->size) {
				res.push_back(item);
			}
		}
		return res;
	}
};



template <typename T> struct Specification
{
	virtual ~Specification() = default;
	virtual bool isSatisfied(const T* item) const = 0;
};

template <typename T> struct AndSpecification : Specification<T>
{
	const Specification<T>& first;
	const Specification<T>& second;

	AndSpecification(const Specification<T>& first, const Specification<T>& second)
		: first(first), second(second) {}

	bool isSatisfied(const T* item) const override
	{
		return first.isSatisfied(item) && second.isSatisfied(item);
	}
};

template <typename T> AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second)
{
	AndSpecification<T> andSpec{ first, second };
	return andSpec;
}

template <typename T> struct Filter
{
	virtual ~Filter() = default;
	virtual std::vector<T*> filter(const std::vector<T*>& items, const Specification<T>& spec) = 0;
};

struct GoodProductFilter : Filter<Product>
{
	std::vector<Product*> filter(const std::vector<Product*>& items, const Specification<Product>& spec) override
	{
		std::vector<Product*> res;
		for (const auto& item : items) {
			if (spec.isSatisfied(item)) {
				res.push_back(item);
			}
		}
		return res;
	}
};

struct ColorSpecification : Specification<Product>
{
	const Color color;

	ColorSpecification(Color color) : color(color) {}

	bool isSatisfied(const Product* item) const override
	{
		return this->color == item->color;
	}
};

struct SizeSpecification : Specification<Product>
{
	const Size size;

	SizeSpecification(Size size) : size(size) {}

	bool isSatisfied(const Product* item) const override
	{
		return this->size == item->size;
	}
};

int main()
{
	Product apple{ "Apple", Color::GREEN, Size::SMALL };
	Product tree{ "Tree", Color::GREEN, Size::LARGE };
	Product house{ "House", Color::RED, Size::LARGE };
	Product chair{ "Chair", Color::BLUE, Size::MEDIUM };

	std::vector<Product*> allProducts{ &apple, &tree, &house, &chair };

	GoodProductFilter pf;

	ColorSpecification greenSpec(Color::GREEN);
	std::vector<Product*> greenProducts = pf.filter(allProducts, greenSpec);
	std::cout << "Green product: ";
	PrintProducts(greenProducts);

	SizeSpecification largeSpec(Size::LARGE);
	std::vector<Product*> largeProducts = pf.filter(allProducts, largeSpec);
	std::cout << "Large product: ";
	PrintProducts(largeProducts);

	std::vector<Product*> greenAndLargeProducts = pf.filter(allProducts, greenSpec && largeSpec);
	std::cout << "Green and Large products: ";
	PrintProducts(greenAndLargeProducts);

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
