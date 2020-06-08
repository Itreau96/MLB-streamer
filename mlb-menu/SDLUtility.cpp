#include "SDLUtility.h"
#include <iostream>
#include <vector>
#include <exception>

// In this exercise I am using a single font that I like
const char* FONT = "..\\AppResources\\bahnschrift.ttf";

SDL_Texture* SDLUtility::TextureFromUrl(SDL_Renderer* renderer, const std::string& url, const std::string& type, CurlUtility& curlUtility)
{
	// Initialize texture data
	SDL_Texture* tex = nullptr;
	MemoryStruct buffer;
	buffer.memory = NULL;
	buffer.size = 0;
	// Try to load image data to texture
	try
	{
		curlUtility.RequestData(url.c_str(), buffer);
		SDL_RWops* rw = SDL_RWFromMem(buffer.memory, buffer.size);
		SDL_Surface* img = IMG_LoadTyped_RW(rw, 1, type.c_str());
		if (img) {
			tex = SDL_CreateTextureFromSurface(renderer, img);
		}
		SDL_FreeSurface(img);
	}
	// Print error on failure
	catch(std::string& e)
	{
		std::cout << e << std::endl;
	}
	// Free useless memory and return
	free(buffer.memory);
	return tex;
}


SDL_Texture* SDLUtility::TextureFromText(const std::string& text, SDL_Color color, int fontSize, SDL_Renderer* renderer)
{
	// Open font
	TTF_Font* font = TTF_OpenFont(FONT, fontSize);
	// Return if error
	if (font == nullptr) {
		return nullptr;
	}
	// Create surface from font
	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
	if (surface == nullptr) {
		// Close font file and return if error
		TTF_CloseFont(font);
		return nullptr;
	}
	// Create texture from font
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	// Return if error
	if (texture == nullptr) {
		TTF_CloseFont(font);
		SDL_FreeSurface(surface);
		return nullptr;
	}
	// Close resources
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}

SDL_Texture* SDLUtility::TextureFromImage(const std::string& path, SDL_Renderer* renderer) {
	// Return texture (nullptr if no image)
	SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
	return texture;
}

void SDLUtility::RenderTexture(SDL_Texture* tex, SDL_Renderer* renderer, int x, int y, int width, int height) {
	// Create rect
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	// Copy texture to new rect position/dimmensions
	SDL_RenderCopy(renderer, tex, NULL, &rect);
}
