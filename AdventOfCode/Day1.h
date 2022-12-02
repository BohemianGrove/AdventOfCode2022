#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <format>
#include <numeric>
#include "AdventOfCode.h"

//Reads a file of integers, each reprensting the elves calories. Each elf is seperate by a line which solely contains a new line.
bool ReadFileD1P1(std::string fileName, std::vector<std::vector<uint64_t>>& result);

//Finds elf with most calories.
bool FindMostCalories(std::vector<std::vector<uint64_t>>& elves, uint64_t& result);

//Computes Day Part 1 answer.
bool ComputeDay1P1();

//Computes Day Part 2 answer.
bool ComputeDay1P2();

//Computes Day 1 answer.
bool ComputeDay1();
