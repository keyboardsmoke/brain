#include "Map.h"
#include "sdl_includes.h"
#include <lodepng.h>

static inline uint32_t GetSurfacePixel(SDL_Surface* surface, uint32_t x, uint32_t y)
{
	int bpp = surface->format->BytesPerPixel;

	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32*)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

bool Map::Load()
{
	SDL_Surface* surface = IMG_Load(m_filename.c_str());

	if (surface == nullptr)
	{
		return false;
	}

	m_width = surface->w;
	m_height = surface->h;

	for (int x = 0; x < surface->w; ++x)
	{
		for (int y = 0; y < surface->h; ++y)
		{
			Uint8 r = 0, g = 0, b = 0, a = 0;

			Uint32 pixel = GetSurfacePixel(surface, x, y);

			SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

			if (a == 0)
			{
				m_values[std::make_pair<int, int>(static_cast<int>(x), static_cast<int>(y))] = EntityType::None;
			}
			else if (a == 0xff)
			{
				if (r == 0 && g == 0 && b == 0)
				{
					// printf("Tree at [x: %d, y: %d]\n", x, y);

					m_values[std::make_pair<int, int>(static_cast<int>(x), static_cast<int>(y))] = EntityType::Tree;
				}
				else if (r == 0xff && g == 0xff && b == 0xff)
				{
					// printf("Water at [x: %d, y: %d]\n", x, y);

					m_values[std::make_pair<int, int>(static_cast<int>(x), static_cast<int>(y))] = EntityType::Water;
				}
				else
				{
					printf("Unsupported entity type at [x: %d, y: %d] color = [%d, %d, %d]\n", x, y, r, g, b);
				}
			}
		}
	}

	SDL_FreeSurface(surface);

	return true;
}