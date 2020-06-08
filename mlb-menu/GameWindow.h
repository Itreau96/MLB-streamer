#pragma once

#include "SDLUtility.h"
#include "CurlUtility.h"
#include "GameData.h"
#include <vector>

/**
* Class used to encapsulate individual MLB game window.
*/
class GameWindow : SDLUtility
{
public:
	/*
	* Class constructor used to generate a game window and render to the screen.
	* @param data Game data used to construct window
	* @param renderer Renderer to render window
	* @param x X position of window
	* @param y Y position of window
	* @param width Width of window in pixels
	* @param height Height of window in pixels
	* @param active Actively selected by user
	* @param curlUtility Curl utility for requesting thumbnail images
	*/
	GameWindow(GameData& data, SDL_Renderer* renderer, int x, int y, int width, int height, bool active, CurlUtility& curlUtility);
	/*
	* Function used to update the position of the game window.
	* @param x X position of window
	* @param x Y position of window
	*/
	void UpdatePosition(int x, int y);
	/*
	* Function used to update dimmensions of window.
	* @param width Width of window in pixels
	* @param height Height of window in pixels
	*/
	void UpdateRect(int width, int height);
	/*
	* Function used to render UI elements of window.
	* @param renderer SDL_Renderer component to render to.
	*/
	void Render(SDL_Renderer* renderer);
	/*
	* Function used to destroy SDL components on close.
	*/
	void Cleanup();
	/*
	* Boolean used to determine if active window. 
	*/
	bool active;
private:
	/*
	* Game data struct.
	*/
	GameData data;
	/*
	* Window textures/UI components.
	*/
	SDL_Texture* texture;
	SDL_Texture* header;
	SDL_Texture* details;
	/*
	* UI component positions/dimmensions.
	*/
	int imgX;
	int imgY;
	int imgWidth;
	int imgHeight;
	int headerX;
	int headerY;
	int detailsX;
	int detailsY;
};