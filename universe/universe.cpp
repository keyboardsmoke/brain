#define SDL_MAIN_HANDLED
#include "universe.h"

#define WINDOW_W (1024 + 1)
#define WINDOW_H 768
#define RENDER_SCALE 1.0f

#include "World.h"
#include "WaterEntity.h"
#include "PlayerEntity.h"
#include "Random.h"

std::vector<PlayerEntity*> g_playerEntities;

static void Render()
{
	for (auto& pe : g_playerEntities)
	{
		if (pe)
		{
			if (!pe->IsMoving() && pe->IsIdle())
			{
				switch (Random::Value<int>(0, 3))
				{
				case 0:
					pe->MoveUp();
					break;
				case 1:
					pe->MoveLeft();
					break;
				case 2:
					pe->MoveRight();
					break;
				case 3:
					pe->MoveDown();
					break;
				}
			}
		}
	}

	// Process world changes here, might as well in the render loop
	// I mean who cares. Single threaded.
	World::Tick();

	// Render the world
	World::Render();
}

int main()
{
	Random::SetSeed();

	Game::RegisterRenderCallback(Render);

	const char* errorMsg = nullptr;

	if (!Game::Initialize("universe", { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H }, &errorMsg, RENDER_SCALE))
	{
		printf("Unable to initialize game [%s]\n", errorMsg);

		return false;
	}

	if (!World::Initialize())
	{
		printf("Unable to initialize world [%s]\n", errorMsg);

		return false;
	}

	// Add entities, or other crap we have to do
	// g_playerEnt = new PlayerEntity(4, 4);
	// World::AddEntity(g_playerEnt);

	for (size_t i = 0; i < 4; ++i)
	{
		SDL_Color newPlayerColor 
		{ 
			Random::Value<uint8_t>(128, 255), 
			Random::Value<uint8_t>(128, 255), 
			Random::Value<uint8_t>(128, 255),
			Random::Value<uint8_t>(128, 255) 
		};

		PlayerEntity* newEnt = new PlayerEntity(newPlayerColor, 4 + i, 2);

		World::AddEntity(newEnt);

		g_playerEntities.push_back(newEnt);
	}

	World::AddEntity(new WaterEntity(1, 1));
	// World::AddEntity(new WaterEntity(2, 1));
	// World::AddEntity(new WaterEntity(1, 2));
	// World::AddEntity(new WaterEntity(2, 2));
	

	// This will loop until close
	Game::Render();

	Game::Shutdown();

	return 0;
}