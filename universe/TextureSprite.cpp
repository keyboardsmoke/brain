#include "Game.h"
#include "TextureSprite.h"

void TextureSprite::RenderFrame(int x, int y, int frameCol, int frameRow)
{
	RenderFrame(x, y, m_frameSize, m_frameSize, frameCol, frameRow);
}

void TextureSprite::RenderFrame(int x, int y, int w, int h, int frameCol, int frameRow)
{
	const int frameX = m_frameSize * frameCol;
	const int frameY = m_frameSize * frameRow;

	SDL_Rect src = { frameX, frameY, m_frameSize, m_frameSize };
	SDL_Rect dst = { x, y, w, h };

	SDL_RenderCopy(Game::GetRenderer(), m_texture.GetSDLTexture(), &src, &dst);
}