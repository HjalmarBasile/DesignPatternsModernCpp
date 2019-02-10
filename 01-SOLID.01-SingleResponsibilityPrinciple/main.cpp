#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Journal
{
	std::string title;
	std::vector<std::string> entries;

	Journal(const std::string& title) : title(title) {};

	void add(const std::string& entry);

	/*
	 Implementing the save method here would be bad:
	 Journal should not be responsible for the persistence layer,
	 if we started adding methods which write to database
	 or to file in every single class, then if we decided
	 to switch to a different db or storage type we would have to
	 change the codebase in many different places.
	 Instead if we pass the responsibility to a specific manager,
	 then we are open to faster changes to the persistence layer in the future
	 */
	// void save(const std::string& filename);
};

void Journal::add(const std::string& entry)
{
	entries.push_back(entry);
}

/*
 This is good: only PersistenceManager will be responsible
 for the persistence layer of the application
*/
struct PersistenceManager
{
	static void save(const Journal& journal, const std::string& filename)
	{
		std::ofstream fout(filename);
		fout << journal.title << '\n';
		for (const std::string& entry : journal.entries) {
			fout << entry << '\n';
		}
		fout << std::endl;
		fout.close();
	}
};

int main()
{
	std::string logfile = "lesson01.01.log";

	Journal journal("My journal");
	journal.add("First chapter: SOLID");
	journal.add("First project: Single Responsibility Principle");

	PersistenceManager pm;
	pm.save(journal, logfile);
	std::cout << "Saved journal to " << logfile << std::endl;
	std::cout << "Push button to exit"<< std::endl;

	std::cin.get();
}
