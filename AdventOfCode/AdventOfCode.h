//This file will serve as a AIO include for each day
#pragma once

#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"

#pragma once
#ifdef _DEBUG
#define POUND #
#define DEBUGPRINT(...) {printf("[%s@%s:%lu]\t",__FILE__, __func__, __LINE__);\
__pragma(warning(suppress : 4473)) \
printf(__VA_ARGS__); printf("\n");}
#else
#define DEBUGPRINT(...) 
#endif