#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <format>
#include <numeric>
#include <unordered_map>
#include <ranges>
#include <utility>

#include "AdventOfCode.h"

//GLOBALS
const int GROUPSIZE = 3;



consteval uint64_t CONSTMATCH();

bool FindShared(std::vector<std::string> input, char& similar);

bool FindShared(std::string InLeft, std::string InRight, char& similar);

bool SplitString(std::string in, std::string& outLeft, std::string& outRight);

//Computes Day 2 Part 1 answer.
bool ComputeDay3P1();

bool ReadFileDay3P1(std::string FileName, std::vector<std::string>& inputs);

bool ReadFileDay3P2(std::string FileName, std::vector<std::vector<std::string>>& inputs);

//Computes Day 2 Part 2 answer.
bool ComputeDay3P2();

//Computes Day 2 answer.
bool ComputeDay3();
