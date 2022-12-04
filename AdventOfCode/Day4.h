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

bool ReadFileDay4P1(std::string FileName, std::vector<std::string>& inputs);

//Computes Day 4 Part 1 answer.
bool ComputeDay4P1();

//Computes Day 4 Part 4 answer.
bool ComputeDay4P2();

//Computes Day 2 answer.
bool ComputeDay4();
