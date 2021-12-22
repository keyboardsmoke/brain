#define SDL_MAIN_HANDLED
#include "universe.h"

#define WINDOW_W (1024 + 1)
#define WINDOW_H 768
#define RENDER_SCALE 1.0f

#include "World.h"
#include "WaterEntity.h"
#include "PlayerEntity.h"
#include "Random.h"

#include <random>
#include <functional>

std::vector<PlayerEntity*> g_playerEntities;

auto rng = std::default_random_engine{};

std::vector<int> CreateRandomMoveChanceArray()
{
	std::vector<int> p{ 0, 1, 2, 3 };
	std::shuffle(p.begin(), p.end(), rng);
	return p;
}

static void TryMove(PlayerEntity* pe)
{
	auto p = CreateRandomMoveChanceArray();

	std::function<bool(PlayerEntity*)> fn[] =
	{
		[](PlayerEntity* pe) -> bool 
		{
			return pe->MoveUp();
		},
		[](PlayerEntity* pe) -> bool
		{
			return pe->MoveDown();
		},
		[](PlayerEntity* pe) -> bool
		{
			return pe->MoveLeft();
		},
		[](PlayerEntity* pe) -> bool
		{
			return pe->MoveRight();
		}
	};

	for (auto& t : p)
	{
		if (fn[t](pe))
			break;
	}
}

static void Render()
{
	for (auto& pe : g_playerEntities)
	{
		if (pe)
		{
			if (pe->IsMoving())
				continue;

			TryMove(pe);
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

	// size 1 only one supported until I rework the collision system...
	// speed is also broken until I'm able to get animation shards slowing/speeding up without breaking other stuff
	// ....

	for (uint16_t i = 0; i < 4; ++i)
	{
		SDL_Color newPlayerColor 
		{ 
			Random::Value<uint8_t>(128, 255), 
			Random::Value<uint8_t>(128, 255), 
			Random::Value<uint8_t>(128, 255),
			Random::Value<uint8_t>(128, 255) 
		};

		PlayerEntity* newEnt = new PlayerEntity(newPlayerColor, 4 + i, 2, 1);

		World::AddEntity(newEnt);

		g_playerEntities.push_back(newEnt);
	}

	// This will loop until close
	Game::Render();

	Game::Shutdown();

	return 0;
}