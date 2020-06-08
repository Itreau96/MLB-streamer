#include "MainWindow.h"
#include <iostream>

const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;

const int GAME_WIDTH = 215;
const int GAME_HEIGHT = 121;
const int GAME_PADDING = 60;;

const std::string BG_PATH = "http://mlb.mlb.com/mlb/images/devices/ballpark/1920x1080/1.jpg";

MainWindow::MainWindow()
{
	// Setup main window
	window = SDL_CreateWindow("MLB", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	// Setup main renderer with optimization flags
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		Cleanup();
		throw "SDL Utility Error: Problem initializing main window!";
	}
	// Set class variables
	currentIndex = 0;
	curlUtility = CurlUtility();
	// Load background texture
	bgTexture = TextureFromUrl(renderer, BG_PATH, "JPG", curlUtility);
	// Generate loading text 
	SDL_Color textColor = { 255, 255, 255 };
	SDL_Texture* loadingTexture = TextureFromText("Loading. Please wait...", textColor, 30, renderer);
	int textW, textH;
	SDL_QueryTexture(loadingTexture, NULL, NULL, &textW, &textH);
	// Render background and initial loading text
	RenderTexture(bgTexture, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderTexture(loadingTexture, renderer, SCREEN_WIDTH / 2 - textW / 2, SCREEN_HEIGHT / 2, textW, textH);
}

void MainWindow::ShiftLeft()
{
	if (currentIndex < gameWindows.size()-1)
	{
		++currentIndex;
		UpdateGameWindows();
	}
}

void MainWindow::ShiftRight()
{
	if (currentIndex > 0)
	{
		--currentIndex;
		UpdateGameWindows();
	}
}

void MainWindow::UpdateGameWindows()
{
	for (unsigned int i = 0; i < gameWindows.size(); ++i)
	{
		// Regenerate positions and width/height based on positions
		int x = SCREEN_WIDTH / 2 - (currentIndex * (GAME_WIDTH + GAME_PADDING) + GAME_WIDTH / 2);
		int y = SCREEN_HEIGHT / 2 - GAME_HEIGHT / 2;
		int width = GAME_WIDTH;
		int height = GAME_HEIGHT;
		bool active = false;
		for (unsigned int i = 0; i < gameWindows.size(); ++i)
		{
			// Expand width/height if selected
			if (currentIndex == i)
			{
				active = true;
				width *= 1.5;
				height *= 1.5;
				y -= GAME_HEIGHT * 0.25;
			}
			else
			{
				active = false;
				width = GAME_WIDTH;
				height = GAME_HEIGHT;
				y = SCREEN_HEIGHT / 2 - GAME_HEIGHT / 2;
			}
			// Update positions of ui elements
			gameWindows[i].UpdatePosition(x, y);
			gameWindows[i].UpdateRect(width, height);
			gameWindows[i].active = active;
			x += width + GAME_PADDING;
		}
	}
}

void MainWindow::AddGameWindows(std::vector<GameData>& games)
{
	// Calculate initial window position/dimmensions
	int x = SCREEN_WIDTH / 2 - (games.size() / 2 * (GAME_WIDTH + GAME_PADDING) + GAME_WIDTH / 2);
	int y = SCREEN_HEIGHT / 2 - GAME_HEIGHT / 2;
	int width = GAME_WIDTH;
	int height = GAME_HEIGHT;
	currentIndex = games.size() / 2;
	bool active = false;
	for (unsigned int i = 0; i < games.size(); ++i)
	{
		// Change dimmensions if selected
		if (currentIndex == i)
		{
			active = true;
			width *= 1.5;
			height *= 1.5;
			y -= GAME_HEIGHT * 0.25;
		}
		else
		{
			active = false;
			width = GAME_WIDTH;
			height = GAME_HEIGHT;
			y = SCREEN_HEIGHT / 2 - GAME_HEIGHT / 2;
		}
		// Add to main window and continue
		AddGameWindow(games[i], x, y, width, height, active);
		x += width + GAME_PADDING;
	}
}

void MainWindow::AddGameWindow(GameData& gameData, int x, int y, int width, int height, bool active)
{
	GameWindow newGame = GameWindow(gameData, renderer, x, y, width, height, active, curlUtility);
	gameWindows.push_back(newGame);
}

void MainWindow::Render()
{
	RenderTexture(bgTexture, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	for (unsigned int i = 0; i < gameWindows.size(); ++i) {
		gameWindows[i].Render(renderer);
	}
}

void MainWindow::Cleanup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	for (unsigned int i = 0; i < gameWindows.size(); i++) {
		gameWindows[i].Cleanup();
	}
}