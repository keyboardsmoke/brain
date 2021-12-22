#pragma once

#include "sdl_includes.h"

#include <optional>
#include <string>

class Texture
{
public:
	Texture(const std::string& filename, std::optional<SDL_Color> transparencyKey = std::nullopt) :
		m_filename(filename), m_transparencyKey(transparencyKey), m_texture(nullptr), m_surface(nullptr), m_textureWidth(0), m_textureHeight(0) {}

	bool Load();
	void Render(int x, int y);
	void Render(int x, int y, int w, int h);

	int GetTextureWidth() { return m_textureWidth; }
	int GetTextureHeight() { return m_textureHeight; }

	SDL_Texture* GetSDLTexture() { return m_texture; }
	SDL_Surface* GetSDLSurface() { return m_surface; }

private:
	std::string m_filename;
	std::optional<SDL_Color> m_transparencyKey;
	SDL_Texture* m_texture;
	SDL_Surface* m_surface;

	int m_textureWidth;
	int m_textureHeight;
};