#pragma once

#include <string>

/**
* Struct used to encapsulate team data.
*/
struct Team
{
	bool winner = false;
	std::string name;
};

/**
* Class used to encapsulate game data.
*/
struct GameData
{
	Team away;
	Team home;
	std::string thumbnail;
	std::string header;
	std::string details;
};