#include <iostream>
#include <string>

/*
 Interface segregation principle states that no client
 should be forced to depend on methods it does not use.
*/

struct Document
{
	std::string text;
};

/*
 IMachine violates the ISP, since the class
 JustAPrinter is forced to implement methods
 that it cannot use.
*/
struct IMachine
{
	virtual void scan(const Document& doc) = 0;
	virtual void print(const Document& doc) = 0;
	virtual void fax(const Document& doc) = 0;
};

struct ScannerPrinterFaxSender : IMachine
{
	void scan(const Document& doc) override
	{
		std::cout << "Scanning the doc" << std::endl;
	}

	void print(const Document& doc) override
	{
		std::cout << "Printing the doc" << std::endl;
	}

	void fax(const Document& doc) override
	{
		std::cout << "Sending the doc via fax" << std::endl;
	}
};

struct JustAPrinter : IMachine
{
	void scan(const Document& doc) override
	{
		throw std::runtime_error("I'm not a scanner");
	}

	void print(const Document& doc) override
	{
		std::cout << "Printing the doc" << std::endl;
	}

	void fax(const Document& doc) override
	{
		throw std::runtime_error("I cannot send fax");
	}
};

/*
 The solution is to segregate the interfaces,
 so that each client will implement only
 what it is able to consume.
*/
struct IScanner
{
	virtual void scan(const Document& doc) = 0;
};

struct IPrinter
{
	virtual void print(const Document& doc) = 0;
};

struct IFaxSender
{
	virtual void fax(const Document& doc) = 0;
};

struct JustAScanner : IScanner
{
	void scan(const Document& doc) override
	{
		std::cout << "Scanning the doc" << std::endl;
	}
};

struct JustAFaxSender : IFaxSender
{
	void fax(const Document& doc) override
	{
		std::cout << "Sending the doc via fax" << std::endl;
	}
};

struct ScannerFaxSender : IScanner, IFaxSender
{
	IScanner& scanner;
	IFaxSender& faxSender;

	ScannerFaxSender(IScanner& scanner, IFaxSender& faxSender)
		: scanner(scanner), faxSender(faxSender) {}

	void scan(const Document& doc) override
	{
		scanner.scan(doc);
	}

	void fax(const Document& doc ) override
	{
		faxSender.fax(doc);
	}
};

int main()
{
	Document doc{ "ISP" };

	JustAPrinter justAPrinter;
	try {
		justAPrinter.print(doc);
		justAPrinter.scan(doc);
	} catch (const std::exception& e) {
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	JustAScanner justAScanner;
	justAScanner.scan(doc);

	JustAFaxSender justAFaxSender;
	justAFaxSender.fax(doc);

	ScannerFaxSender machine{ justAScanner, justAFaxSender };
	machine.scan(doc);
	machine.fax(doc);

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
