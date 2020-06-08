#pragma once

#include "SDLUtility.h"
#include "CurlUtility.h"
#include "GameWindow.h"
#include "GameData.h"
#include <vector>

/*
* Main window logic/UI for application.
*/
class MainWindow : SDLUtility
{
public:
	/*
	* Default constructor.
	*/
	MainWindow();
	/*
	* Adds initial list of games to main window.
	* @param games List of game data objects
	*/
	void AddGameWindows(std::vector<GameData>& games);
	/*
	* Shifts items to the left (right game selected).
	*/
	void ShiftLeft();
	/*
	* Shifts items to the right (left game selected).
	*/
	void ShiftRight();
	/*
	* Renders textures to main renderer (called once per frame).
	*/
	void Render();
	/*
	* Destroys SDL render objects and textures.
	*/
	void Cleanup();
	/*
	* Application central renderer.
	*/
	SDL_Renderer* renderer;
private:
	/*
	* Adds individual game window to main window.
	* @param gameData Reference to game data to compose window
	* @param x X position
	* @param y Y position
	* @param width Width of window in pixels
	* @param height Height of window in pixels
	* @param active Boolean value indicating whether or not window is actively selected
	*/
	void AddGameWindow(GameData& gameData, int x, int y, int width, int height, bool active);
	/*
	* Updates game windows based on current selection.
	*/
	void UpdateGameWindows();
	/*
	* Central application window.
	*/
	SDL_Window* window;
	/*
	* Window background texture.
	*/
	SDL_Texture* bgTexture;
	/*
	* Utility for loading background image at given URL.
	*/
	CurlUtility curlUtility;
	/*
	* Current game selection index.
	*/
	unsigned int currentIndex;
	/*
	* List of game window instances.
	*/
	std::vector<GameWindow> gameWindows;
};