#pragma once

#include <string>
#include <optional>
#include <unordered_map>
#include "Texture.h"
#include "TextureSprite.h"
#include "Animation.h"

class TextureCache
{
public:
	static SDL_Surface* LoadSurface(const std::string& filename, std::optional<SDL_Color> colorKey);
	static SDL_Texture* LoadTexture(const std::string& filename);

	static size_t LoadedSurfaceCount();
	static size_t LoadedTextureCount();
};