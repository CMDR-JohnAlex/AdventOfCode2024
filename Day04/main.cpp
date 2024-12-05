#include "../Utils/Utils.h"

auto Part1(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 1");

	for (const auto& line : input)
	{
		STRIP(std::cout << line << '\n');
	}

	int xmasCount = 0;

	// My plan is to loop every character on every line and check for an X.
	// If we find an X, we will check around it to see if we can find an M.
	// If we find an M, we will keep going in that direction to see if we can find an A.
	// If we find an A, we will keep going in that direction to see if we can find an S.
	// If we find an S, we increment a counter and continue searching for the next X.

	// This is pretty crappy, but should work.
	// To make it better, we could probably use a recursive function to check in all directions.
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input.size(); j++)
		{
			if (input[i][j] == 'X')
			{
				try
				{
					if (input[i].at(j + 1) == 'M')
					{
						if (input[i].at(j + 2) == 'A')
						{
							if (input[i].at(j + 3) == 'S')
							{
								xmasCount++;
							}
						}
					}
				}
				catch (const std::out_of_range& e)
				{
					// Do nothing
				}
				try
				{
					if (input.at(i + 1)[j] == 'M')
					{
						if (input.at(i + 2)[j] == 'A')
						{
							if (input.at(i + 3)[j] == 'S')
							{
								xmasCount++;
							}
						}
					}
				}
				catch (const std::out_of_range& e)
				{
					// Do nothing
				}
				try
				{
					if (input[i].at(j - 1) == 'M')
					{
						if (input[i].at(j - 2) == 'A')
						{
							if (input[i].at(j - 3) == 'S')
							{
								xmasCount++;
							}
						}
					}
				}
				catch (const std::out_of_range& e)
				{
					// Do nothing
				}
				try
				{
					if (input.at(i - 1)[j] == 'M')
					{
						if (input.at(i - 2)[j] == 'A')
						{
							if (input.at(i - 3)[j] == 'S')
							{
								xmasCount++;
							}
						}
					}
				}
				catch (const std::out_of_range& e)
				{
					// Do nothing
				}
				try
				{
					if (input.at(i + 1).at(j + 1) == 'M')
					{
						if (input.at(i + 2).at(j + 2) == 'A')
						{
							if (input.at(i + 3).at(j + 3) == 'S')
							{
								xmasCount++;
							}
						}
					}
				}
				catch (const std::out_of_range& e)
				{
					// Do nothing
				}
				try
				{
					if (input.at(i - 1).at(j - 1) == 'M')
					{
						if (input.at(i - 2).at(j - 2) == 'A')
						{
							if (input.at(i - 3).at(j - 3) == 'S')
							{
								xmasCount++;
							}
						}
					}
				}
				catch (const std::out_of_range& e)
				{
					// Do nothing
				}
				try
				{
					if (input.at(i + 1).at(j - 1) == 'M')
					{
						if (input.at(i + 2).at(j - 2) == 'A')
						{
							if (input.at(i + 3).at(j - 3) == 'S')
							{
								xmasCount++;
							}
						}
					}
				}
				catch (const std::out_of_range& e)
				{
					// Do nothing
				}
				try
				{
					if (input.at(i - 1).at(j + 1) == 'M')
					{
						if (input.at(i - 2).at(j + 2) == 'A')
						{
							if (input.at(i - 3).at(j + 3) == 'S')
							{
								xmasCount++;
							}
						}
					}
				}
				catch (const std::out_of_range& e)
				{
					// Do nothing
				}
			}
		}
	}

	return xmasCount;
}

auto Part2(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 2");

	for (const auto& line : input)
	{
		STRIP(std::cout << line << '\n');
	}

	return 0;
}

int main(int argc, char** argv)
{
	Utils::Timer timer("Day 04");
	try
	{
#ifdef INPUT_TESTING
		std::vector<std::string> lines = Utils::ReadFile("PuzzleTestInput.txt");
#else
		std::vector<std::string> lines = Utils::ReadFile("PuzzleInput.txt");
#endif
		auto result1 = Part1(lines);
		Utils::CheckResult(result1, 18);

		auto result2 = Part2(lines);
		Utils::CheckResult(result2, 9);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}