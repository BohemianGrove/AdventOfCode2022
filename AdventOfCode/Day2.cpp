#include "Day2.h"


//Keeps track of the game state. The values should be tied to the s_OpCodeMap values. Should not be changed as values rely on it
enum GameState
{
	LOSE = 0,
	TIE = 1,
	WIN = 2,
};
static_assert(LOSE == 0 && TIE == 1 && WIN == 2, "GameState values have changed. Please update the s_OpCodeMap values and make sure appropriate casts are fixed");

//Score values are calculated by adding +1 to the key... So Rock = 1, Paper = 2, Scissors = 3
static const std::unordered_map<char, int> s_OpCodeMap = 
{
	//rock
	{'X', GameState::LOSE},
	{'A', GameState::LOSE},
	//paper
	{'B', GameState::TIE},
	{'Y', GameState::TIE},
	//scissors
	{'C', GameState::WIN},
	{'Z', GameState::WIN},
};
const decltype(s_OpCodeMap.at(0)) s_OpCodeMapMaxKey = std::ranges::max_element(s_OpCodeMap, [](const auto a, const auto b) { return a.second < b.second; })->second;

//Checks to see if we won rock paper scizzors
//Returns result in GameState variable, returns success status in bool
bool CheckWin(char theirs, char ours, GameState &gameState)
{
	//check if NULL
	if (theirs == NULL || ours == NULL)
	{
		DEBUGPRINT("INVALID INPUT");
		return false;
	}
	
	//Check if they exist
	auto theirsIt = s_OpCodeMap.find(theirs);
	auto oursIt = s_OpCodeMap.find(ours);
	if (theirsIt == s_OpCodeMap.end() || oursIt == s_OpCodeMap.end())
	{
		DEBUGPRINT("INVALID INPUT");
		return false;
	}
	
	if (theirsIt->second == oursIt->second)
	{
		gameState = TIE;
		return true;
	}
	
	if ((theirsIt->second + 1) % (s_OpCodeMapMaxKey + 1) == oursIt->second)
	{
		gameState = WIN;
		return true;
	}

	gameState = LOSE;
	return true;
}

//Tells us what value we need to make the gamestate
bool MakeGameState(char theirs, char& ours, GameState gameState)
{
	auto theirsIt = s_OpCodeMap.find(theirs);
	if (theirsIt == s_OpCodeMap.end())
	{
		DEBUGPRINT("INVALID INPUT");
		return false;
	}
	auto theirsKey = theirsIt->second;
	
	int key = 0;
	ours = -1;
	decltype(s_OpCodeMap.begin()) temp;//A placeholder for the key we're looking for.. Used in the LOSE case
	
	//Calculate what we need to tie, win or lose based off of gameState
	switch (gameState)
	{
	case LOSE:
		//Special case if theirs is 0.
		if (theirsKey == 0)
			key = theirsKey + s_OpCodeMapMaxKey;
		else
			key = (theirsKey - 1) % s_OpCodeMapMaxKey;

		//Checking if our key exists
		temp = std::ranges::find_if(s_OpCodeMap, [key](auto a) { return a.second == key; });
		if (temp == s_OpCodeMap.end())
		{
			DEBUGPRINT("UNABLE TO FIND KEY");
			return false;
		}
		
		ours = temp->first;
		break;
		
	case TIE:
		ours = theirs;
		break;
		
	case WIN:
		key = (theirsKey + 1) % ((std::ranges::max_element(s_OpCodeMap, [](auto a, auto b) { return a.second < b.second; }))->second + 1);
		
		//Checking if the key exists
		temp = std::ranges::find_if(s_OpCodeMap, [key](auto a) { return a.second == key; });
		if (temp == s_OpCodeMap.end())
		{
			DEBUGPRINT("UNABLE TO FIND KEY");
			return false;
		}
		ours = temp->first;
		break;
		
	default:
		DEBUGPRINT("INVALID INPUT");
		return false;
	}
	
	if(ours == -1)
	{
		DEBUGPRINT("INVALID INPUT");
		return false;
	}
	
	return true;
	
}

//Reads a file consisting of two characters per line, seperated by a space. The first character is the opponents move, the second is our move.
bool ReadFileD2P1(std::string fileName, std::vector<std::pair<char, char>>& result)
{
	std::ifstream file;
	file = std::ifstream(fileName);
	if (!file)
	{
		DEBUGPRINT("UNABLE TO OPEN FILE %s", fileName.c_str());
		return false;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		std::stringstream ss(line);
		char theirs = NULL;
		char ours = NULL;
		ss >> theirs >> ours;
		result.push_back(std::make_pair(theirs, ours));
	}

	return true;
}

//Used to keep track of how many points each game state is worth.
enum class Scores
{
	Win = 6,
	Lose = 0,
	Tie = 3,
};

void foo(uint64_t bar)
{
	bar = static_cast<decltype(bar)>(25);
}

bool CalculateScore(GameState gameState, char move, int& result)
{
	//Check if s_OpCodeMap contains move
	if (s_OpCodeMap.find(move) == s_OpCodeMap.end())
	{
		DEBUGPRINT("INVALID MOVE");
		return false;
	}

	switch (gameState)
	{
	case WIN:
		result = static_cast<decltype(+result)>(Scores::Win) + s_OpCodeMap.find(move)->second + 1;
		break;
	case LOSE:
		result = static_cast<decltype(+result)>(Scores::Win) + s_OpCodeMap.find(move)->second + 1;
		break;
	case TIE:
		result = static_cast<decltype(+result)>(Scores::Win) + s_OpCodeMap.find(move)->second + 1;
		break;
	default:
		DEBUGPRINT("INVALID GAME STATE");
		return false;
	}
	return true;
}

//Computes Day 2 Part 1 answer.
bool ComputeDay2P1()
{
	std::vector<std::pair<char, char>> moves;
	if (!ReadFileD2P1("Day2P1.txt", moves))
	{
		DEBUGPRINT("UNABLE TO READ FILE");
		return false;
	}

	uint64_t score = 0;
	uint64_t wins = 0;
	uint64_t losses = 0;
	uint64_t ties = 0;
	for (auto move : moves)
	{
		GameState gameState;
		int result = 0;
		if (!CheckWin(move.first, move.second, gameState))
		{
			DEBUGPRINT("UNABLE TO CHECK WIN");
			return false;
		}
		CalculateScore(gameState, move.second, result);
		switch (gameState)
		{
		case WIN:
			score += result;
			wins++;
			break;
		case LOSE:
			score += result;
			losses++;
			break;
		case TIE:
			score += result;
			ties++;
			break;
		default:
			DEBUGPRINT("INVALID GAME STATE");
			return false;
		}
	}

	std::cout << "Day 2 Part 1: " << score << std::endl;
	std::cout << "Wins: " << wins << std::endl;
	std::cout << "Losses: " << losses << std::endl;
	std::cout << "Ties: " << ties << std::endl;
	
	return true;
}

//Computes Day 2 Part 2 answer.
bool ComputeDay2P2()
{
	std::vector<std::pair<char, char>> moves;
	if (!ReadFileD2P1("Day2P1.txt", moves))
	{
		DEBUGPRINT("UNABLE TO READ FILE");
		return false;
	}

	uint64_t score = 0;
	uint64_t wins = 0;
	uint64_t losses = 0;
	uint64_t ties = 0;
	for (auto move : moves)
	{
		//Checking if key exists
		if (s_OpCodeMap.find(move.second) == s_OpCodeMap.end())
		{
			DEBUGPRINT("INVALID MOVE");
			return false;
		}
		
		if (s_OpCodeMap.find(move.second) == s_OpCodeMap.end())
		{
			DEBUGPRINT("INVALID MOVE");
			return false;
		}
		
		GameState gameState = static_cast<GameState>(s_OpCodeMap.find(move.second)->second);
		int result = 0;
		char ours = NULL;
		if (!MakeGameState(move.first, ours, gameState))
		{
			DEBUGPRINT("UNABLE TO MAKE GAME STATE");
			return false;
		}
		
		CalculateScore(gameState, ours, result);
		switch (gameState)
		{
		case WIN:
			score += result;
			wins++;
			break;
		case LOSE:
			score += result;
			losses++;
			break;
		case TIE:
			score += result;
			ties++;
			break;
		default:
			DEBUGPRINT("INVALID GAME STATE");
			return false;
		}
	}

	std::cout << "Day 2 Part 2: " << score << std::endl;
	std::cout << "Wins: " << wins << std::endl;
	std::cout << "Losses: " << losses << std::endl;
	std::cout << "Ties: " << ties << std::endl;

	return true;
}

bool ComputeDay2()
{
	if (!ComputeDay2P1())
	{
		DEBUGPRINT("UNABLE TO COMPUTE DAY 2 PART 1");
		return false;
	}

	if (!ComputeDay2P2())
	{
		DEBUGPRINT("UNABLE TO COMPUTE DAY 2 PART 2");
		return false;
	}
	
	return true;
}

