#include "Game.h"
#include "TextureSprite.h"

void TextureSprite::RenderFrame(int x, int y, int frameCol, int frameRow)
{
	const int frameX = m_frameSize * frameCol;
	const int frameY = m_frameSize * frameRow;
	const int frameW = m_frameSize;
	const int frameH = m_frameSize;

	SDL_Rect src = { frameX, frameY, frameW, frameH };
	SDL_Rect dst = { x, y, frameW, frameH };

	SDL_RenderCopy(Game::GetRenderer(), m_texture.GetSDLTexture(), &src, &dst);
}