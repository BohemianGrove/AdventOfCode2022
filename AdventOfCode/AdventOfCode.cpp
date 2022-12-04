#pragma once
#include "AdventOfCode.h"
#include <iostream>

int main()
{
	if(!ComputeDay1())
	{
		DEBUGPRINT("FAILED TO COMPUTE DAY 1");
	}

	if (!ComputeDay2())
	{
		DEBUGPRINT("FAILED TO COMPUTE DAY 2");
	}

	if (!ComputeDay3())
	{
		DEBUGPRINT("FAILED TO COMPUTE DAY 3");
	}

	if (!ComputeDay4())
	{
		DEBUGPRINT("FAILED TO COMPUTE DAY 4");
	}
	
	return 0;
}