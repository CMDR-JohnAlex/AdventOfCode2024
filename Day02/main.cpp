#include "../Utils/Utils.h"

auto Part1(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 1");

	int safeCount = 0;
	for (const auto& line : input)
	{
#ifdef INPUT_TESTING
		std::cout << line << '\n';
#endif

		std::istringstream inputStringStream(line);
		int numberNew;
		int numberOld;
		bool isIncrease = false;
		bool isDecrease = false;
		bool isSafe = true;

		inputStringStream >> numberOld;
#ifdef INPUT_TESTING
		std::cout << "NumberOld: " << numberOld << '\n';
#endif

		while (inputStringStream >> numberNew)
		{
#ifdef INPUT_TESTING
			std::cout << "NumberNew: " << numberNew << '\n';
#endif

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
#ifdef INPUT_TESTING
				std::cout << "Unsafe, range\n";
#endif
				isSafe = false;
				break;
			}

			// Can't increase and decrease
			if (isIncrease && isDecrease)
			{
#ifdef INPUT_TESTING
				std::cout << "Unsafe, increase & decrease\n";
#endif
				isSafe = false;
				break;
			}

			numberOld = numberNew;
		}

		if (isSafe)
		{
#ifdef INPUT_TESTING
			std::cout << "Safe\n";
#endif
			safeCount++;
		}
	}

	return safeCount;
}

// Returns the index of the first number that is not safe. If given 1 2 3 and 2 compared to 3 is not safe, it will return the index of 2.
// If all numbers are safe, it will return -1.
int FindUnsafeIndex(const std::vector<int>& numbers)
{
	int numberNew;
	int numberOld;
	bool isIncrease = false;
	bool isDecrease = false;
	bool isSafe = true;

	int index = 0;
	numberOld = numbers[index];
	for (index = 1; index < numbers.size(); index++)
	{
		numberNew = numbers[index];
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
#ifdef INPUT_TESTING
			std::cout << "Unsafe, range\n";
#endif
			isSafe = false;
			break;
		}

		// Can't increase and decrease
		if (isIncrease && isDecrease)
		{
#ifdef INPUT_TESTING
			std::cout << "Unsafe, increase & decrease\n";
#endif
			isSafe = false;
			break;
		}

		numberOld = numberNew;
	}

	if (!isSafe)
	{
		return index - 1;
	}
	return -1;
}

auto Part2(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 2");

	int safeCount = 0;
	for (const auto& line : input)
	{
#ifdef INPUT_TESTING
		std::cout << "Line: " << line << '\n';
#endif

		std::istringstream inputStringStream(line);
		std::vector<int> numbers;

		while (!inputStringStream.eof())
		{
			int number;
			inputStringStream >> number;
			numbers.push_back(number);
		}

		int unsafeIndex = FindUnsafeIndex(numbers);
		if (unsafeIndex == -1)
		{
			std::cout << "Safe\n";
			safeCount++;
		}
		else // I'm not very proud of this mess...
		{
#ifdef INPUT_TESTING
			std::cout << "Unsafe detected at index " << unsafeIndex << ". Trying to remove the unsafe number and check again.\n";
#endif
			std::vector<int> numbersCopy = numbers;
			numbersCopy.erase(numbersCopy.begin() + unsafeIndex);
#ifdef INPUT_TESTING
			std::cout << "Correction Attempt 1: (Remove index)\n";
			for (int i = 0; i < numbersCopy.size(); i++)
			{
				std::cout << numbersCopy[i] << ' ';
			}
			std::cout << '\n';
#endif
			if (FindUnsafeIndex(numbersCopy) == -1)
			{
#ifdef INPUT_TESTING
				std::cout << "Safe\n";
#endif
				safeCount++;
				continue; // Ignore the rest, continue to the next input line.
			}

			numbersCopy = numbers;
			numbersCopy.erase(numbersCopy.begin() + unsafeIndex + 1);
#ifdef INPUT_TESTING
			std::cout << "Correction Attempt 2: (Remove index + 1)\n";
			for (int i = 0; i < numbersCopy.size(); i++)
			{
				std::cout << numbersCopy[i] << ' ';
			}
			std::cout << '\n';
#endif
			if (FindUnsafeIndex(numbersCopy) == -1)
			{
#ifdef INPUT_TESTING
				std::cout << "Safe\n";
#endif
				safeCount++;
				continue; // Ignore the rest, continue to the next input line.
			}

			// If the unsafeIndex is at 1, perhaps it is index 0 that is the problem?
			if (unsafeIndex == 1)
			{
				numbersCopy = numbers;
				numbersCopy.erase(numbersCopy.begin());
#ifdef INPUT_TESTING
				std::cout << "Correction Attempt 3: (Remove first)\n";
				for (int i = 0; i < numbersCopy.size(); i++)
				{
					std::cout << numbersCopy[i] << ' ';
				}
				std::cout << '\n';
#endif
				if (FindUnsafeIndex(numbersCopy) == -1)
				{
#ifdef INPUT_TESTING
					std::cout << "Safe\n";
#endif
					safeCount++;
					continue; // Ignore the rest, continue to the next input line.
				}
			}

#ifdef INPUT_TESTING
			std::cout << "No correction(s) found. Unsafe.\n";
#endif
		}
	}

	return safeCount;
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
		Utils::CheckResult(result2, 4);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}