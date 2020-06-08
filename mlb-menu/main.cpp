#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "GameData.h"
#include "MainWindow.h"
#include "SDL_image.h"
#include "GameParser.h"
#include <string>
#include <iostream>
#include <thread>

const std::string IN_PATH = "http://statsapi.mlb.com/api/v1/schedule?hydrate=game(content(editorial(recap))),decisions&date=2018-06-10&sportId=1";

/*
* Initializes SDL library objects
*/
int InitLibs()
{
	// Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init error" << std::endl;
		return 1;
	}

	// Initialize img subsystem
	if (((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) ||
		((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)) {
		std::cout << "IMG_Init error" << std::endl;
		return 1;
	}

	// Initialize font subsystem
	if (TTF_Init() != 0) {
		std::cout << "TTF_Init error" << std::endl;
		return 1;
	}

	return 0;
}

int SdlLoop(MainWindow& mainWindow)
{
	// Loop variables
	bool quit = false;
	bool moving = false;
	SDL_Event e;

	while (!quit)
	{
		// Handle quit events
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		// Move thumbnails left and right based on key states
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			if (!moving)
			{
				mainWindow.ShiftRight();
				moving = true;
			}
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			if (!moving)
			{
				mainWindow.ShiftLeft();
				moving = true;
			}
		}
		else
		{
			// Moving used to prevent continuous movement while key is pressed
			if (moving)
			{
				moving = false;
			}
		}
		// Re-render at the end of each frame
		SDL_RenderClear(mainWindow.renderer);
		mainWindow.Render();
		SDL_RenderPresent(mainWindow.renderer);
	}

	return 0;
}

void Cleanup(MainWindow& mainWindow)
{
	mainWindow.Cleanup();
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

int main(int argc, char* argv[])
{
	// Initialize libraries
	InitLibs();

	// Initialize main menu
	MainWindow mainWindow = MainWindow();

	// Render loading screen
	SDL_RenderPresent(mainWindow.renderer);

	// Parse file (need to optimize this in future)
	GameParser parser = GameParser();
	parser.ParseFile(IN_PATH);

	// Create game windows
	mainWindow.AddGameWindows(parser.games);

	// Run render/event loop
	SdlLoop(mainWindow);

	// Cleanup SDL objects
	Cleanup(mainWindow);

	return 0;
}