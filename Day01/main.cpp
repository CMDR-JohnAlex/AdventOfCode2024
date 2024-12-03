#include "../Utils/Utils.h"
#include <iostream>
#include <algorithm>
#include <sstream>

auto Part1(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 1");

	std::vector<int> list1;
	std::vector<int> list2;

	for (const auto& line : input)
	{
		OUTPUT(line << '\n');

		std::string number1;
		std::string number2;

		// The two numbers can be separated using a stringstream since they are
		// separated by a space (or three).
		std::istringstream inputStringStream(line);
		inputStringStream >> number1 >> number2;

		OUTPUT("Number 1: " << number1 << '\n');
		OUTPUT("Number 2: " << number2 << '\n');

		list1.push_back(std::stoi(number1));
		list2.push_back(std::stoi(number2));
	}

	std::sort(list1.begin(), list1.end(), [](int a, int b) { return a < b; });
	std::sort(list2.begin(), list2.end(), [](int a, int b) { return a < b; });

	OUTPUT("List 1 Sorted:\n");
	for (const auto& i : list1)
	{
		OUTPUT(i << '\n');
	}

	OUTPUT("List 2 Sorted:\n");
	for (const auto& i : list2)
	{
		OUTPUT(i << '\n');
	}

	OUTPUT("List difference:\n");
	int sum = 0;
	for (int i = 0; i < list1.size(); i++)
	{
		int diff = abs(list1[i] - list2[i]);
		OUTPUT(diff << '\n');
		sum += diff;
	}

	return sum;
}

auto Part2(const std::vector<std::string>& input)
{
	Utils::Timer timer("Part 2");

	std::vector<int> list1;
	std::vector<int> list2;

	for (const auto& line : input)
	{
		OUTPUT(line << '\n');

		std::string number1;
		std::string number2;

		std::istringstream inputStringStream(line);
		inputStringStream >> number1 >> number2;

		OUTPUT("Number 1: " << number1 << '\n');
		OUTPUT("Number 2: " << number2 << '\n');

		list1.push_back(std::stoi(number1));
		list2.push_back(std::stoi(number2));
	}

	/*
	To find the similarity score, we need to loop each element of list1 and
	multiply it by the amount of times that element is found in list2.
	*/
	// similarityScore = list1[i] * count of list1[i] in list2
	int similarityScoreSum = 0;
	for (int i = 0; i < list1.size(); i++)
	{
		int count = static_cast<int>(std::count(list2.begin(), list2.end(), list1[i]));
		int similarityScore = list1[i] * count;
		OUTPUT("Instances of " << list1[i] << ": " << count << '\n');
		OUTPUT("Similarity score: " << similarityScore << '\n');
		similarityScoreSum += similarityScore;
	}

	return similarityScoreSum;
}

int main(int argc, char** argv)
{
	Utils::Timer timer("Day 01");
	try
	{
#ifdef INPUT_TESTING
		std::vector<std::string> lines = Utils::ReadFile("PuzzleTestInput.txt");
#else
		std::vector<std::string> lines = Utils::ReadFile("PuzzleInput.txt");
#endif
		auto result1 = Part1(lines);
		Utils::CheckResult(result1, 11);

		auto result2 = Part2(lines);
		Utils::CheckResult(result2, 31);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}

	return 0;
}