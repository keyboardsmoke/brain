#include "Game.h"
#include <unordered_map>

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Surface* g_windowSurface = nullptr;
SDL_Texture* g_backBuffer = nullptr;
SDL_Rect g_windowRect{};
SDL_Rect g_windowScaledRect{};
uint8_t* g_bbPixels = nullptr;
int g_bbPitch = 0;
float g_renderScale = 0.0f;

std::vector<Game::RenderCallback> g_renderCallbacks;

SDL_Window* Game::GetWindow()
{
	return g_window;
}

SDL_Surface* Game::GetWindowSurface()
{
	return g_windowSurface;
}

SDL_Texture* Game::GetBackBuffer()
{
	return g_backBuffer;
}

SDL_Renderer* Game::GetRenderer()
{
	return g_renderer;
}

const SDL_Rect& Game::GetWindowRect()
{
	return g_windowRect;
}

const SDL_Rect& Game::GetWindowScaledRect()
{
	return g_windowScaledRect;
}

const float Game::GetWindowScale()
{
	return g_renderScale;
}

static bool GetSupportedRenderers(std::unordered_map<std::string, int>& supportedDrivers)
{
	for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i)
	{
		SDL_RendererInfo rendererInfo = {};
		if (SDL_GetRenderDriverInfo(i, &rendererInfo) != 0)
			return false;

		if (rendererInfo.name == nullptr)
			return false;

		supportedDrivers[rendererInfo.name] = i;
	}
	
	return true;
}

bool Game::Initialize(const std::string& windowName, const SDL_Rect& windowRect, const char** errorMsg, float renderScale)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		*errorMsg = SDL_GetError();

		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
	{
		printf("Warning: Nearest pixel texture filtering not enabled!\n");
	}

	g_window = SDL_CreateWindow(windowName.c_str(), // creates a window 
		windowRect.x, windowRect.y, windowRect.w, windowRect.h, 0);

	if (g_window == nullptr)
	{
		*errorMsg = SDL_GetError();

		return false;
	}

	std::unordered_map<std::string, int> renderers;

	if (!GetSupportedRenderers(renderers))
	{
		*errorMsg = SDL_GetError();

		return false;
	}

	/*
 *  This variable is case insensitive and can be set to the following values:
 *    "direct3d"
 *    "opengl"
 *    "opengles2"
 *    "opengles"
 *    "metal"
 *    "software"
 
	Supported Renderer [direct3d]
	Supported Renderer [opengl]
	Supported Renderer [software]
	Supported Renderer [opengles2]
	*/

	for (auto r : renderers)
	{
		printf("Supported Renderer [%s]\n", r.first.c_str());
	}

	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	g_renderer = SDL_CreateRenderer(g_window, -1, render_flags);

	if (g_renderer == nullptr)
	{
		*errorMsg = SDL_GetError();

		return false;
	}

	SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);

	g_windowSurface = SDL_GetWindowSurface(g_window);

	if (g_windowSurface == nullptr)
	{
		*errorMsg = SDL_GetError();

		return false;
	}

	// 64 x 48 now lol
	SDL_RenderSetScale(g_renderer, renderScale, renderScale);

	g_renderScale = renderScale;

	memcpy(&g_windowRect, &windowRect, sizeof(SDL_Rect));

	g_windowScaledRect.x = g_windowRect.x;
	g_windowScaledRect.y = g_windowRect.y;
	g_windowScaledRect.w = g_windowRect.w / static_cast<int>(renderScale);
	g_windowScaledRect.h = g_windowRect.h / static_cast<int>(renderScale);

	return true;
}

void Game::RegisterRenderCallback(RenderCallback cb)
{
	g_renderCallbacks.emplace_back(cb);
}

void Game::Render()
{
	int close = 0;

	while (!close)
	{
		SDL_Event event;

		// Events mangement 
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				close = 1;
				break;
			}
		}

		SDL_LockTexture(g_backBuffer, nullptr, (void**)&g_bbPixels, &g_bbPitch);

		SDL_UnlockTexture(g_backBuffer);

		SDL_RenderClear(g_renderer);

		for (auto& r : g_renderCallbacks)
		{
			r();
		}

		SDL_RenderPresent(g_renderer);

		// Force 60fps
		SDL_Delay(1000 / 60);
	}
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(g_renderer);

	g_renderer = nullptr;

	SDL_DestroyWindow(g_window);

	g_window = nullptr;
}