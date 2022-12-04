#include "Day4.h"

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

bool ComputeDay4P1()
{
	std::vector<std::string> inputs;
	if (!ReadFileDay4P1("Day4.txt", inputs))
	{
		DEBUGPRINT("Failed to read file");
		return false;
	}
	return false;
}

bool ComputeDay4P2()
{
	return false;
}

bool ComputeDay4()
{
	if (!ComputeDay4P1())
	{
		DEBUGPRINT("Failed to compute Day 4 Part 1");
		return false;
	}
	
	if (!ComputeDay4P2())
	{
		DEBUGPRINT("Failed to compute Day 4 Part 2");
		return false;
	}
	
	return true;
}
