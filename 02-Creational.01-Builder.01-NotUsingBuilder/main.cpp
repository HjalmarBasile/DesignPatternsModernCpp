#include <iostream>
#include <string>
#include <sstream>

/*
 This is an example of how bad it is to construct simple html code
 without giving any structure to the code. We are relying entirely on the fact
 that we know the correct html syntax, but we should instead find a better design
 and build and API which always construct well formed html code.
 
 Builder pattern is the solution to this problem.
*/
int main()
{
	/* Example 1 */
	std::string text = "hello";
	std::string output;

	output += "<p>";
	output += text;
	output += "</p>";
	std::cout << output << std::endl;

	/* Example 2 */
	std::ostringstream ssout;
	std::string words[] = { "hello", "world" };
	ssout << "<ul>\n";
	for (const std::string& word : words) {
		ssout << "  <li>" << word << "</li>\n";
	}
	ssout << "</ul>\n";
	std::cout << ssout.str() << std::endl;

	std::cout << "Push button to exit" << std::endl;
	std::cin.get();
	return 0;
}
