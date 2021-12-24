#include "Map.h"
#include "sdl_includes.h"

struct MapColorKeyEntry
{
	Map::EntityType type;
	uint32_t color;
};

MapColorKeyEntry g_colorKeys[] =
{
	{ Map::EntityType::None, 0x00000000 },
	{ Map::EntityType::Tree, 0x000000ff },
	{ Map::EntityType::Water, 0xffffffff }
};

static inline Map::EntityType GetEntityTypeFromColor(Uint32 x, Uint32 y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Uint32 color = static_cast<Uint32>(r << 24 | g << 16 | b << 8 | a);

	for (size_t i = 0; i < _countof(g_colorKeys); ++i)
	{
		if (color == g_colorKeys[i].color)
		{
			return g_colorKeys[i].type;
		}
	}

	// Warning
	printf("Unsupported entity type at [x: %d, y: %d] color = [%d, %d, %d]\n", x, y, r, g, b);

	return Map::EntityType::None;
}

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
			Uint32 pixel = GetSurfacePixel(surface, x, y);

			Uint8 r = 0, g = 0, b = 0, a = 0;
			SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

			m_values[std::make_pair(x, y)] = GetEntityTypeFromColor(x, y, r, g, b, a);
		}
	}

	SDL_FreeSurface(surface);

	return true;
}