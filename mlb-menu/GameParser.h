#pragma once

#include "GameData.h"
#include "CurlUtility.h"
#include <string>
#include <vector>
#include <map>

class GameParser
{
public:
	/*
	* Default constructor.
	*/
	GameParser();
	/*
	* Parses game data given a valid URL.
	* @param urlPath Path to json feed.
	*/
	void ParseFile(const std::string& urlPath);
	/*
	* Gets game data given an list index.
	* @param index Index of data in list.
	* @return Game data at given index.
	*/
	GameData& GetGame(unsigned int& index);
	/*
	* Adds game to list.
	* @param gameData Game data to add.
	*/
	void AddGame(GameData gameData);
	/*
	* Gets game data given an list index.
	* @param index Index of data in list.
	*/
	unsigned int GetNumGames();
	/*
	* List of game data (parsed).
	*/
	std::vector<GameData> games;
private:
	/*
	* Helper function used to parse out away team struct values.
	* @param istringstream String stream for json data.
	* @param data Game data to update.
	*/
	void GetAway(std::istringstream& stringStream, GameData& data);
	/*
	* Helper function used to parse out home team struct values.
	* @param istringstream String stream for json data.
	* @param data Game data to update.
	*/
	void GetHome(std::istringstream& stringStream, GameData& data);
	/*
	* Helper function used to parse out title and detail text for game data.
	* @param istringstream String stream for json data.
	* @param data Game data to update.
	*/
	void GetText(std::istringstream& stringStream, GameData& data);
	/*
	* Helper function used to parse out title and detail text for game data.
	* @param istringstream String stream for json data.
	* @param data Game data to update.
	*/
	void GetThumbnail(std::istringstream& stringStream, GameData& data);
	/*
	* Helper function used to parse out json data from string.
	* @param token Json token to parse.
	* @return Value given json string.
	*/
	std::string GetJsonValue(std::string& token);
	/*
	* Helper function used to correct broken thumbnail URLs.
	* @param url URL string to modify.
	* @return Corrected url string.
	*/
	std::string CorrectUrl(std::string& url);
	/*
	* Curl utility used to retrieve Json data.
	*/
	CurlUtility curlUtility;
};