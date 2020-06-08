#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "CurlUtility.h"

/**
* Helper class used to encapsulate SDL rendering functionality for application UI
*/
class SDLUtility
{
public:
	/**
	* Virtual function used to destroy sdl items.
	*/
	virtual void Cleanup() = 0;
protected:
	/**
	* Helper function used to generate a texture file from a URL.
	* @param ren SDL renderer to draw the texture
	* @param url The URL api call to the image resource
	* @param type The file extension/file type
	* @param curlUtility The CurlUtility instance used to retrieve the image resource
	* @return An SDL_Texture containing the rendered image
	*/
	SDL_Texture* TextureFromUrl(SDL_Renderer* renderer, const std::string& url, const std::string& type, CurlUtility& curlUtility);
	/**
	* Helper function used to generate texture from string value.
	* @param text The URL api call to the image resource
	* @param color The RGB color values for the texture
	* @param fontSize Font size of text in pixels
	* @param ren SDL renderer to draw the texture
	* @return An SDL_Texture containing the rendered text
	*/
	SDL_Texture* TextureFromText(const std::string& text, SDL_Color color, int fontSize, SDL_Renderer* renderer);
	/**
	* Helper function used to generate texture from image file.
	* @param path Path to the image file to render
	* @param renderer SDL_Renderer to render image
	* @return An SDL_Texture containing the rendered image
	*/
	SDL_Texture* TextureFromImage(const std::string& path, SDL_Renderer* renderer);
	/**
	* Helper function used to render sdl texture.
	* @param tex Texture to render
	* @param renderer SDL_Renderer to render texture
	*/
	void RenderTexture(SDL_Texture* tex, SDL_Renderer* renderer, int x, int y, int width, int height);
};
