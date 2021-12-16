#pragma once

#include "sdl_includes.h"
#include "Texture.h"

#include <string>

class TextureSprite
{
public:
	TextureSprite(const std::string& filename, int frameSize, const SDL_Color& transparencyKey = { 255, 0, 255, 0 }) :
		m_filename(filename), m_frameSize(frameSize), m_texture(filename, transparencyKey) {}

	bool Load() { return m_texture.Load(); }
	void RenderFrame(int x, int y, int frameCol, int frameRow);

	Texture* GetTexture() { return &m_texture; }

private:
	std::string m_filename;

	int m_frameSize;

	Texture m_texture;
};