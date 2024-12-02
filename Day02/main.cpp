#include "../Utils/Utils.h"

auto Part1(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 1");

	int safeCount = 0;
	for (const auto& line : input)
	{
		std::cout << line << '\n';

		std::istringstream inputStringStream(line);
		int numberNew;
		int numberOld;
		bool isIncrease = false;
		bool isDecrease = false;
		bool isSafe = true;

		inputStringStream >> numberOld;
		std::cout << "NumberOld: " << numberOld << '\n';

		while (inputStringStream >> numberNew)
		{
			std::cout << "NumberNew: " << numberNew << '\n';

			if (numberOld < numberNew)
			{
				isIncrease = true;
			}
			else if (numberOld > numberNew)
			{
				isDecrease = true;
			}

			// At least 1, at most 3
			if (!(abs(numberNew - numberOld) >= 1) || !(abs(numberNew - numberOld) <= 3))
			{
				std::cout << "Unsafe, range\n";
				isSafe = false;
				break;
			}

			// Can't increase and decrease
			if (isIncrease && isDecrease)
			{
				std::cout << "Unsafe, increase & decrease\n";
				isSafe = false;
				break;
			}

			numberOld = numberNew;
		}

		if (isSafe)
		{
			std::cout << "Safe\n";
			safeCount++;
		}
	}

	return safeCount;
}

auto Part2(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 2");

	for (const auto& line : input)
	{
		std::cout << line << '\n';
	}

	return 0;
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
		Utils::CheckResult(result1, 2);

		auto result2 = Part2(lines);
		Utils::CheckResult(result2, 0);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}