#include "Day3.h"

//Creates a bitmap with all entries filled in, in compile time. This is used to calculate our match string. For example,. if group size is 3, it will be the binary number b111
consteval uint64_t CONSTMATCH()
{
	return (1 << GROUPSIZE) - 1;
}

bool FindShared(std::vector<std::string> input, char &similar)
{
	similar = NULL;
	std::unordered_map<char, int> characters;

	//We can find the unique value by checking it against a bit map, if all bits are set.
	static_assert(GROUPSIZE <= 64, "ALGORITHM USES A BITMAP ON A 64 BIT INTEGER. FIX ALGORITHM TO SUPPORT LARGE GROUPS");
	if (input.size() != GROUPSIZE)
	{
		DEBUGPRINT("INVALID INPUT. SIZE MUST BE GROUPSIZE");
		return false;
	}
	
	int i = 0;

	for (auto str : input)
	{
		for (auto c : str)
		{
			characters[c] |= 1 << i;
		}
		i++;
	}

	uint64_t match = CONSTMATCH();
	auto it = characters | std::views::keys | std::views::filter([characters, match](char n) {return (characters.at(n) & match) == match; });

	int size = 0;
	for (auto i : it)
	{
		if (size++ > 0)
		{
			DEBUGPRINT("ERROR SHOULD ONLY BE ONE MATCH");
			return false;
		}
		similar = i;
	}

	if (similar == NULL)
	{
		DEBUGPRINT("NO MATCHES FOUND!");
		return false;
	}

	return true;;
}

bool FindShared(std::string InLeft, std::string InRight, char& similar)
{
	similar = NULL;
	std::unordered_map<char, int> characters;

	//We can find the unique value by checking if it's odd and != 1, as we add 2 everytime it appears in right, and it will have 1 if found in left.
	for (auto c : InLeft)
	{
		characters[c] = 1;
	}

	for (auto c : InRight)
	{
		characters[c] += 2;
	}

	int found = 0;
	for (auto i : characters)
	{
		if (found > 1)
		{
			DEBUGPRINT("ERROR SHOULD ONLY BE ONE MATCH");
			return false;
		}

		if (i.second % 2 == 1 && i.second != 1)
		{
			found++;
		}
	}

	auto it = characters | std::views::keys | std::views::filter([characters](char n) {return characters.at(n) % 2 == 1 && characters.at(n) != 1; });

	int size = 0;
	for (auto i : it)
	{
		if (size++ > 0)
		{
			DEBUGPRINT("ERROR SHOULD ONLY BE ONE MATCH");
			return false;
		}
		similar = i;
	}

	if (similar == NULL)
	{
		DEBUGPRINT("NO MATCHES FOUND!");
		return false;
	}

	return true;;
}

//Splits the string in half into the two variables
bool SplitString(std::string in, std::string &outLeft, std::string &outRight)
{
	//Check if the string is empty or odd number, which means invalid input
	if (in.empty() || in.size() % 2 != 0)
	{
		DEBUGPRINT("Invalid input string");
		return false;
	}
	
	size_t half = in.size() / 2;
	outLeft = in.substr(0, half);
	outRight = in.substr(half, in.size() - half);
	return true;
}


bool ReadFileDay3P1(std::string FileName, std::vector<std::string> &inputs)
{
    //read file
	std::ifstream file(FileName);
	if (!file.is_open())
	{
		DEBUGPRINT("UNABLE TO OPEN FILE %s", FileName.c_str());
		return false;
	}
	
	std::string line;
	while (std::getline(file, line))
	{
		inputs.push_back(line);
	}
	
	return true;
}

bool ReadFileDay3P2(std::string FileName, std::vector<std::vector<std::string>>& inputs)
{
	//read file
	std::ifstream file(FileName);
	if (!file.is_open())
	{
		DEBUGPRINT("UNABLE TO OPEN FILE %s", FileName.c_str());
		return false;
	}

	//Need to resize our vector
	inputs.resize(10);
	
	int i = 0;
	for(i = 0; file.good() ; i++)
	{
		//Need to check if we need to resize our vector
		if (i >= inputs.size() - 1)
		{
			inputs.resize(inputs.size() * 2);
		}

		std::string line;
		for (int j = 0; j < GROUPSIZE && std::getline(file, line); j++)
		{
			inputs[i].push_back(line);
		}
	}

	//We need to check the final index to make sure it's our group size and we have valid input
	inputs.resize(i - 1);
	if (inputs.back().size() != GROUPSIZE)
	{
		DEBUGPRINT("INVALUD GROUP COUNT. BAD INPUT??");
		return false;
	}

	return true;
}



bool ComputeDay3P2()
{
	std::vector<std::vector<std::string>> inputs;
	std::vector<char> hits;

	if (!ReadFileDay3P2("Day3.txt", inputs))
	{
		return false;
	}

	char common;
	for (auto in : inputs)
	{
		if (!FindShared(in, common))
		{
			return false;
		}
		hits.push_back(common);
	}

	uint64_t sum = 0;
	for (auto i : hits)
	{
		//We can calculate the score by the position in the alphabet. Uppercase characters start from 27, so 'z' - 'a' + 1
		if (islower(i))
			sum += i - 'a' + 1;
		else
			sum += i - 'A' + 1 + 'z' - 'a' + 1;
	}

	std::cout << "Day 3 Part 2: " << sum << std::endl;

	return true;


}


bool ComputeDay3P1()
{
	std::vector<std::string> inputs;
	if (!ReadFileDay3P1("Day3.txt", inputs))
	{
		DEBUGPRINT("UNABLE TO READ FILE");
		return false;
	}
	
	std::vector<char> hits; //Matches for similar characters.
	for (auto i : inputs)
	{
		std::string left, right;
		if (!SplitString(i, left, right))
		{
			DEBUGPRINT("UNABLE TO SPLIT STRING");
			return false;
		}

		char similar;
		if (!FindShared(left, right, similar))
		{
			DEBUGPRINT("UNABLE TO FIND SHARED CHARACTERS");
			return false;
		}
		
		hits.push_back(similar);
	}	
	
	uint64_t sum = 0;
	for (auto i : hits)
	{
		//We can calculate the score by the position in the alphabet. Uppercase characters start from 27, so 'z' - 'a' + 1
		if (islower(i))
			sum += i - 'a' + 1;
		else
			sum += i - 'A' + 1 + 'z' - 'a' + 1;
	}

	std::cout << "Day 3 Part 1: " << sum << std::endl;
	
	return true;

}

bool ComputeDay3()
{
	if (!ComputeDay3P1())
	{
		DEBUGPRINT("ERROR COMPUTING DAY 3 P1");
		return false;
	}
	
	if (!ComputeDay3P2())
	{
		DEBUGPRINT("ERROR COMPUTING DAY 3 P2");
		return false;
	}

	return true;
}
