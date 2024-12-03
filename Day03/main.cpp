#include "../Utils/Utils.h"
#include <regex>
#include <tuple>

auto Part1(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 1");

	std::string inputOneLine = "";
	for (const auto& line : input)
	{
		OUTPUT(line << '\n');
		inputOneLine += line;
	}

	std::regex regex("(mul)\\((\\d{1,3}),(\\d{1,3})\\)");
	std::smatch match;
	std::vector<std::tuple<std::string, int, int>> matches;
	int result = 0;

	std::string::const_iterator searchStart(inputOneLine.cbegin());
	while (std::regex_search(searchStart, inputOneLine.cend(), match, regex))
	{
		OUTPUT("Match: " << match.str() << '\n');
		for (const auto& subMatch : match)
		{
			OUTPUT("  Submatch: " << subMatch << '\n');
		}

		// emplace_back constructs the tuple in place, avoiding a copy! Woah!
		matches.emplace_back(match[1].str(), std::stoi(match[2]), std::stoi(match[3]));
		searchStart = match.suffix().first;
	}

	OUTPUT("Matches as tuples:\n");
	for (const auto& [operation, num1, num2] : matches)
	{
		OUTPUT(operation << " " << num1 << " " << num2 << '\n');
	}

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

	for (const auto& line : input)
	{
		OUTPUT(line << '\n');
	}

	return 0;
}

int main(int argc, char** argv)
{
	Utils::Timer timer("Day 00");
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