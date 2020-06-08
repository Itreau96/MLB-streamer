#include "GameParser.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <iostream>

GameParser::GameParser()
{
	curlUtility = CurlUtility();
}

void GameParser::ParseFile(const std::string& urlPath)
{
	// Initialize
	MemoryStruct buffer;
	buffer.memory = NULL;
	buffer.size = 0;

	try
	{
		// Request data
		curlUtility.RequestData(urlPath, buffer);
		// Stream line at a time
		std::istringstream strVal = (std::istringstream)buffer.memory; // NOTE: not very efficient! Need optimization in future...
		std::string line;
		bool waiting = false;
		bool searchStarted = false;
		GameData currentData = GameData();
		while (std::getline(strVal, line)) {
			// If first game hasn't been reached, wait until it has been
			if (!searchStarted)
			{
				if (line.find("gamePk") != std::string::npos)
				{
					searchStarted = true;
				}
			}
			else
			{
				// If new game has been reached, save off and start another
				if (line.find("gamePk") != std::string::npos)
				{
					AddGame(currentData);
					currentData = GameData();
					waiting = false;
				}
				else
				{
					// Waiting until new game has been reached...
					if (!waiting)
					{
						// Save off parsed values of interest
						GetAway(strVal, currentData);
						GetHome(strVal, currentData);
						GetText(strVal, currentData);
						GetThumbnail(strVal, currentData);
						waiting = true;
					}
				}
			}
		}
	}
	// If error loading file, write out
	catch (std::string& e)
	{
		std::cout << e << std::endl;
	}
	// Free memory
	free(buffer.memory);
}

void GameParser::GetAway(std::istringstream& stringStream, GameData& data)
{
	std::string line;
	std::string name;
	bool winner = false;
	while (std::getline(stringStream, line)) {
		if (line.find("\"name\"") != std::string::npos)
		{
			name = GetJsonValue(line);
		}
		else if (line.find("\"isWinner\" : true") != std::string::npos)
		{
			winner = true;
			break;
		}
		else if (line.find("\"isWinner\" : false") != std::string::npos)
		{
			winner = false;
			break;
		}
	}
	data.away.name = name;
	data.away.winner = winner;
}

void GameParser::GetHome(std::istringstream& stringStream, GameData& data)
{
	std::string line;
	std::string name;
	bool winner = false;
	while (std::getline(stringStream, line)) {
		if (line.find("\"name\"") != std::string::npos)
		{
			name = GetJsonValue(line);
		}
		else if (line.find("\"isWinner\" : true") != std::string::npos)
		{
			winner = true;
			break;
		}
		else if (line.find("\"isWinner\" : false") != std::string::npos)
		{
			winner = false;
			break;
		}
	}
	data.home.name = name;
	data.home.winner = winner;
}

void GameParser::GetText(std::istringstream& stringStream, GameData& data)
{
	std::string line;
	std::string headline;
	std::string title;
	while (std::getline(stringStream, line)) {
		if (line.find("\"headline\"") != std::string::npos)
		{
			headline = GetJsonValue(line);
			title = data.home.name + " vs " + data.away.name;
			break;
		}
	}
	data.details = headline;
	data.header = title;
}

void GameParser::GetThumbnail(std::istringstream& stringStream, GameData& data)
{
	std::string line;
	std::string url;
	bool resolutionFound = false;
	while (std::getline(stringStream, line)) {
		if (resolutionFound)
		{
			if (line.find("\"src\" : ") != std::string::npos)
			{
				resolutionFound = true;
				std::string rawUrl = GetJsonValue(line);
				url = CorrectUrl(rawUrl);
				break;
			}
		}
		else
		{
			if (line.find("800x448") != std::string::npos) // Only interested in 800x448 resolution thumbnails
			{
				resolutionFound = true;
			}
		}
	}
	data.thumbnail = url;
}

std::string GameParser::GetJsonValue(std::string& token)
{
	std::string temp;
	unsigned int start = token.find_last_of(":") + 3;
	unsigned int end = token.size() - start - 2;
	temp = token.substr(start, end);
	return temp;
}

std::string GameParser::CorrectUrl(std::string& url)
{
	// At present CURL fails if securea.mlb is included in URL. Temp fix is to replace with redirect URL.
	std::string temp;
	unsigned int start = url.find_first_of(".") + 1;
	temp = "https://content." + url.substr(start);
	return temp;
}

GameData& GameParser::GetGame(unsigned int& index)
{
    return this->games.at(index);
}

void GameParser::AddGame(GameData gameData)
{
    this->games.push_back(gameData);
}

unsigned int GameParser::GetNumGames()
{
    return this->games.size();
}