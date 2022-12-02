#include "Day1.h"

//Reads a file of integers, each reprensting the elves calories. Each elf is seperate by a line which solely contains a new line.
bool ReadFileD1P1(std::string fileName, std::vector<std::vector<uint64_t>> &result)
{	
	std::ifstream file;
	file = std::ifstream(fileName);
	if (!file)
	{
		DEBUGPRINT("UNABLE TO OPEN FILE %s", fileName.c_str());
		return false;
	}
	
	//Need to update our size.
	result.resize(10);
	
	std::string line;
	size_t i = 0; //Elf index
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			if (i >= result.size() - 1)
				result.resize(result.size() * 2);
			i++;
			continue;
		}
		std::stringstream ss(line);
		uint64_t calories = 0;
		ss >> calories;
		result.at(i).push_back(calories);
	}

	return true;
}


//Finds elf with most calories.
bool FindMostCalories(std::vector<std::vector<uint64_t>> &elves, uint64_t &result)
{
	uint64_t maxCalories = 0;
	uint64_t maxCaloriesIndex = 0;
	for (size_t i = 0; i < elves.size(); i++)
	{
		uint64_t calories = std::reduce(elves[i].begin(), elves[i].end());
		if (calories > maxCalories)
		{
			maxCalories = calories;
			maxCaloriesIndex = i;
		}
	}

	result = maxCaloriesIndex;
	return (result != -1) ? true : false;
}

//Computes Day 1 Part 1 answer.
bool ComputeDay1P1()
{
	std::vector<std::vector<uint64_t>> elves;

	if (!ReadFileD1P1("Day1P1.txt", elves))
	{
		DEBUGPRINT("UNABLE TO READ FILE");
		return false;
	}

	uint64_t result = 0;
	if (!FindMostCalories(elves, result) )
	{
		DEBUGPRINT("UNABLE TO FIND MOST CALORIES");
		return false;
	}

	std::cout << "D1P1: The elf with the most calories is elf " << result << " with " << std::reduce(elves[result].begin(), elves[result].end()) << " cookies." << std::endl;

	return true;
}

bool ComputeDay1P2()
{
	const int ElfCount = 3; //How many elves we're summing
	uint64_t topElves[ElfCount] = { 0 };
	uint64_t sum = 0;
	std::vector<std::vector<uint64_t>> elves;

	if (!ReadFileD1P1("Day1P1.txt", elves))
	{
		DEBUGPRINT("UNABLE TO READ FILE");
		return false;
	}

	for (size_t i = 0; i < ElfCount; i++)
	{
		uint64_t result = 0;
		if (!FindMostCalories(elves, result))
		{
			DEBUGPRINT("UNABLE TO FIND MOST CALORIES OF INDEX %zu", i);
			return false;
		}
		sum += std::reduce(elves[result].begin(), elves[result].end());
		topElves[i] = result;

		//Removing elf and then computing again.
		elves.erase(elves.begin() + result);
	}

	std::cout << "D1P2: The elves with the most calories are elves " << topElves[0] << ", " << topElves[1] << ", and " << topElves[2] << " with " << sum << " cookies." << std::endl;
	
	return true;
}

//Computes Day 1 answer.
bool ComputeDay1()
{
	if (!ComputeDay1P1())
	{
		DEBUGPRINT("UNABLE TO COMPUTE DAY 1 PART 1");
		return false;
	}

	if (!ComputeDay1P2())
	{
		DEBUGPRINT("UNABLE TO COMPUTE DAY 1 PART 2");
		return false;
	}

	return true;
}