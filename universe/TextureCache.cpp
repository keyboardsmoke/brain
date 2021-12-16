#include "TextureCache.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Surface*> g_surfaces;
std::unordered_map<std::string, Texture*> g_textures;

SDL_Surface* TextureCache::LoadSurface(const std::string& filename, std::optional<SDL_Color> colorKey)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (surface == nullptr)
	{
		printf("Unable to load image from surface [%s]\n", IMG_GetError());

		return nullptr;
	}

	if (colorKey.has_value())
	{
		const Uint32 transKeyColor = SDL_MapRGB(surface->format, colorKey->r, colorKey->g, colorKey->b);

		SDL_SetColorKey(surface, SDL_TRUE, transKeyColor);
	}

	g_surfaces[filename] = surface;

	return surface;
}

SDL_Texture* TextureCache::LoadTexture(const std::string& filename)
{
	auto surf = g_surfaces.find(filename);

	if (surf == g_surfaces.end())
		return nullptr;

	SDL_Surface* surface = surf->second;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::GetRenderer(), surface);

	if (texture == nullptr)
	{
		printf("Unable to create texture from surface [%s]\n", SDL_GetError());

		return nullptr;
	}

	return texture;
}

size_t TextureCache::LoadedSurfaceCount()
{
	return g_surfaces.size();
}

size_t TextureCache::LoadedTextureCount()
{
	return g_textures.size();
}