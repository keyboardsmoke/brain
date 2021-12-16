#include "Game.h"
#include "Texture.h"
#include "TextureCache.h"

bool Texture::Load()
{
	m_surface = TextureCache::LoadSurface(m_filename, m_transparencyKey);

	if (m_surface == nullptr)
	{
		printf("Unable to load image from surface [%s]\n", IMG_GetError());

		return false;
	}

	m_texture = TextureCache::LoadTexture(m_filename);

	if (m_texture == nullptr)
	{
		printf("Unable to create texture from surface [%s]\n", SDL_GetError());

		return false;
	}

	if (SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height) != 0)
	{
		printf("Unable to query texture dims [%s]\n", SDL_GetError());

		return false;
	}

	return true;
}

void Texture::Render(int x, int y)
{
	SDL_Rect rect = { x, y, m_width, m_height };
	SDL_RenderCopy(Game::GetRenderer(), m_texture, nullptr, &rect);
}