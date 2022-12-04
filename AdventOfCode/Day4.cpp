#include "Day4.h"

struct TaskRange
{
	int Start;
	int End;
};

bool CompareTaskRangeAny(TaskRange a, TaskRange b, bool& overlapping)
{
	//Check if the ranges overlap at all
	overlapping = (a.Start <= b.End && b.Start <= a.End) || (b.Start <= a.End && a.Start <= b.End);

	return true;
}

bool CompareTaskRange(TaskRange a, TaskRange b, bool &overlapping)
{
	overlapping = (a.Start <= b.Start && a.End >= b.End) || (b.Start <= a.Start && b.End >= a.End);
	
	return true;
}

bool StringToTask(std::string input, TaskRange &TaskLeft, TaskRange &TaskRight)
{
	//Split a string on comma
	std::string left;
	std::string right;
	std::string::size_type comma = input.find(',');
	if (comma == std::string::npos)
	{
		DEBUGPRINT("Invalid input string");
		return false;
	}
	left = input.substr(0, comma);
	right = input.substr(comma + 1);
	
	//Split the strings, in the format START-END into the TASKRANGE struct
	std::string::size_type dash = left.find('-');
	if (dash == std::string::npos)
	{
		DEBUGPRINT("Invalid input string");
		return false;
	}
	TaskLeft.Start = std::stoi(left.substr(0, dash));
	TaskLeft.End = std::stoi(left.substr(dash + 1));
	
	dash = right.find('-');
	if (dash == std::string::npos)
	{
		DEBUGPRINT("Invalid input string");
		return false;
	}
	TaskRight.Start = std::stoi(right.substr(0, dash));
	TaskRight.End = std::stoi(right.substr(dash + 1));
	
	return true;

}


bool ReadFileDay4P1(std::string FileName, std::vector<std::string>& inputs)
{
	//Read all lines from the file
	std::ifstream file(FileName);
	if (!file.is_open())
	{
		DEBUGPRINT("Failed to open file %s", FileName.c_str());
		return false;
	}
	
	std::string line;
	while (std::getline(file, line))
	{
		inputs.push_back(line);
	}

	return true;
}


bool ComputeDay4()
{
	std::vector<std::string> inputs;
	if (!ReadFileDay4P1("Day4.txt", inputs))
	{
		DEBUGPRINT("Failed to read file");
		return false;
	}

	int overlapCount = 0;
	int overlapCountAny = 0;

	//Loop through all the inputs
	for (auto& str : inputs)
	{
		TaskRange TaskLeft;
		TaskRange TaskRight;
		if (!StringToTask(str, TaskLeft, TaskRight))
		{
			DEBUGPRINT("Failed to convert string to task");
			return false;
		}
		bool overlapping = false;
		if (!CompareTaskRange(TaskLeft, TaskRight, overlapping))
		{
			DEBUGPRINT("Failed to compare tasks");
			return false;
		}

		if (overlapping)
		{
			overlapCount++;
		}

		if (!CompareTaskRangeAny(TaskLeft, TaskRight, overlapping))
		{
			DEBUGPRINT("Failed to compare tasks");
			return false;
		}

		if (overlapping)
		{
			overlapCountAny++;
		}
	}

	std::cout << "Day 4 Part 1: " << overlapCount << std::endl;
	std::cout << "Day 4 Part 2: " << overlapCountAny << std::endl;

	return true;
}
