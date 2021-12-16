#pragma once

#include <vector>
#include <string>

#include "sdl_includes.h"

class Game
{
public:
	typedef void (*RenderCallback)();

	static SDL_Window* GetWindow();
	static SDL_Surface* GetWindowSurface();
	static SDL_Texture* GetBackBuffer();
	static SDL_Renderer* GetRenderer();
	static const SDL_Rect& GetWindowRect();
	static const SDL_Rect& GetWindowScaledRect();

	static const float GetWindowScale();

	static bool Initialize(const std::string& windowName, const SDL_Rect& windowRect, const char** errorMsg, float renderScale = 1.0f);
	static void RegisterRenderCallback(RenderCallback cb);
	static void Render();
	static void Shutdown();
};