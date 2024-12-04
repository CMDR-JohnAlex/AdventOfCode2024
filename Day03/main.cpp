#include "../Utils/Utils.h"
#include <regex>
#include <tuple>

auto Part1(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 1");

	// Combine all lines into one string
	std::string inputOneLine = "";
	for (const auto& line : input)
	{
		STRIP(std::cout << line << '\n');
		inputOneLine += line;
	}

	// Regex to match "mul(#,#)" where # is a number with 1-3 digits
	// The regex is split into 3 capture groups: "mul", "num1", "num2"
	std::regex regex("(mul)\\((\\d{1,3}),(\\d{1,3})\\)");
	std::smatch matchGroup;
	std::vector<std::tuple<std::string, int, int>> matches;
	int result = 0;

	/*
	std::regex_search() only returns the first match, so we use a while loop
	and an iterator to search the rest of the input. When a match is found, we
	store the capture groups in a tuple and then move the iterator to the end
	of the match to search the rest of the input.
	*/
	std::string::const_iterator searchStart(inputOneLine.cbegin());
	while (std::regex_search(searchStart, inputOneLine.cend(), matchGroup, regex))
	{
		STRIP(
			std::cout << "Match: " << matchGroup.str() << '\n';
			for (const auto& subMatch : matchGroup)
			{
				std::cout << "  Submatch: " << subMatch << '\n';
			}
		);

		// emplace_back() constructs the tuple in place, avoiding a copy! Woah!
		matches.emplace_back(matchGroup[1].str(), std::stoi(matchGroup[2]), std::stoi(matchGroup[3]));
		searchStart = matchGroup.suffix().first;
	}

	STRIP(
		std::cout << "Matches as tuples:\n";
		for (const auto& [operation, num1, num2] : matches)
		{
			std::cout << operation << " " << num1 << " " << num2 << '\n';
		}
	);

	for (const auto& [operation, num1, num2] : matches)
	{
		if (operation == "mul")
		{
			result += num1 * num2;
		}
	}

	return result;
}

auto Part2(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 2");

	// Combine all lines into one string
	std::string inputOneLine = "";
	for (const auto& line : input)
	{
		STRIP(std::cout << line << '\n');
		inputOneLine += line;
	}

	// Regex is the same as above, but will also capture "do()" and "don't()"
	std::regex regex("(mul)\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\)");
	std::smatch matchGroup;
	/*
	In-case you didn't notice, I included a string in the tuple for the
	operation (like multiplication) because I assumed part 2 would require it.
	Part 2 did something different...
	*/
	std::vector<std::tuple<std::string, int, int>> matches;
	int result = 0;
	bool isEnabled = true; // Remember, the default is true

	/*
	std::regex_search() only returns the first match, so we use a while loop
	and an iterator to search the rest of the input. When a match is found, we
	store the capture groups in a tuple and then move the iterator to the end
	of the match to search the rest of the input.
	*/
	std::string::const_iterator searchStart(inputOneLine.cbegin());
	while (std::regex_search(searchStart, inputOneLine.cend(), matchGroup, regex))
	{
		STRIP(
			std::cout << "Match: " << matchGroup.str() << '\n';
			for (const auto& subMatch : matchGroup)
			{
				std::cout << "  Submatch: " << subMatch << '\n';
			}
		);

		if (matchGroup.str() == "do()")
		{
			isEnabled = true;
		}
		else if (matchGroup.str() == "don't()")
		{
			isEnabled = false;
		}
		else if (isEnabled)
		{
			// emplace_back() constructs the tuple in place, avoiding a copy! Woah!
			matches.emplace_back(matchGroup[1].str(), std::stoi(matchGroup[2]), std::stoi(matchGroup[3]));
		}
		searchStart = matchGroup.suffix().first;
	}

	STRIP(
		std::cout << "Matches as tuples:\n";
		for (const auto& [operation, num1, num2] : matches)
		{
			std::cout << operation << " " << num1 << " " << num2 << '\n';
		}
	);

	for (const auto& [operation, num1, num2] : matches)
	{
		if (operation == "mul")
		{
			result += num1 * num2;
		}
	}

	return result;
}

int main(int argc, char** argv)
{
	Utils::Timer timer("Day 02");
	try
	{
#ifdef INPUT_TESTING
		std::vector<std::string> lines = Utils::ReadFile("PuzzleTestInput.txt");
#else
		std::vector<std::string> lines = Utils::ReadFile("PuzzleInput.txt");
#endif
		auto result1 = Part1(lines);
		Utils::CheckResult(result1, 161);

		auto result2 = Part2(lines);
		Utils::CheckResult(result2, 48);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}