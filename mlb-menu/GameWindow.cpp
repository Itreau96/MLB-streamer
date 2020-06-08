#include "GameWindow.h"

const int TEXT_OFFSET = 20;

GameWindow::GameWindow(GameData& data, SDL_Renderer* renderer, int x, int y, int width, int height, bool active, CurlUtility& curlUtility)
{
	this->active = active;
	// Setup background image
	texture = TextureFromUrl(renderer, data.thumbnail.c_str(), "JPG", curlUtility);
	// Setup header text
	SDL_Color textColor = { 255, 255, 255 };
	header = TextureFromText(data.header, textColor, 10, renderer);
	details = TextureFromText(data.details, textColor, 10, renderer);
	// Make sure loaded ok
	if (texture == nullptr || header == nullptr || details == nullptr) {
		Cleanup();
	}
	// Get image location
	imgX = x;
	imgY = y;
	// Get image dimmensions
	imgWidth = width;
	imgHeight = height;
	// Get header location
	headerX = x;
	headerY = y - TEXT_OFFSET;
	// Get footer location
	detailsX = x;
	detailsY = y + imgHeight + TEXT_OFFSET;
	// Render!
	Render(renderer);
}

void GameWindow::UpdatePosition(int x, int y)
{
	// Recalculate UI positions
	imgX = x;
	imgY = y;
	headerX = x;
	headerY = y - TEXT_OFFSET;
	detailsX = x;
	detailsY = y + imgHeight + TEXT_OFFSET;
}

void GameWindow::UpdateRect(int width, int height)
{
	// Set UI dimmensions
	imgWidth = width;
	imgHeight = height;
}

void GameWindow::Render(SDL_Renderer* renderer)
{
	// Only render text for active element
	if (active)
	{
		int iW, iH;
		int jW, jH;
		SDL_QueryTexture(header, NULL, NULL, &iW, &iH);
		SDL_QueryTexture(details, NULL, NULL, &jW, &jH);
		RenderTexture(header, renderer, headerX + imgWidth / 2 - iW / 2, headerY, iW, iH);
		RenderTexture(details, renderer, detailsX + imgWidth / 2 - jW / 2, detailsY, jW, jH);
	}
	// Render image texture
	RenderTexture(texture, renderer, imgX, imgY, imgWidth, imgHeight);
}

void GameWindow::Cleanup()
{
	SDL_DestroyTexture(texture);
}