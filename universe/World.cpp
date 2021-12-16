#include "Game.h"
#include "World.h"
#include "Texture.h"
#include "TextureSprite.h"
#include "Entity.h"
#include "Random.h"
#include "PerlinNoise.h"
#include "WorldEntity.h"

#define GRID_SIZE 16

std::vector<Entity*> g_entities;
std::unordered_map<Entity*, std::pair<uint16_t, uint16_t>> g_entityPositions;

TextureSprite tiles("../Resources/Tiny16/basictiles.png", GRID_SIZE);

static std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>> GrassTiles;

uint32_t World::GetGridSize()
{
	return GRID_SIZE;
}

void World::GetGridDims(uint16_t& cols, uint16_t& rows)
{
	cols = GetGridMaxColumns();
	rows = GetGridMaxRows();
}

uint16_t World::GetGridMaxColumns()
{
	return Game::GetWindowRect().w / GRID_SIZE;
}

uint16_t World::GetGridMaxRows()
{
	return Game::GetWindowRect().h / GRID_SIZE;
}

bool World::IsValidGridPosition(uint16_t col, uint16_t row)
{
	uint16_t mc, mr;
	GetGridDims(mc, mr);
	return ((col >= 0 && col <= mc) && (row >= 0 && row <= mr));
}

bool World::GetGridFromPos(uint16_t x, uint16_t y, uint16_t& col, uint16_t& row)
{
	uint16_t nx = (x - (x % World::GetGridSize()));
	uint16_t ny = (y - (y % World::GetGridSize()));
	uint16_t gc = x / World::GetGridSize();
	uint16_t gr = y / World::GetGridSize();

	if (!IsValidGridPosition(gc, gr))
		return false;

	col = gc;
	row = gr;

	return true;
}

bool World::GetPosFromGrid(uint16_t col, uint16_t row, uint16_t& x, uint16_t& y)
{
	if (!IsValidGridPosition(col, row))
		return false;

	x = col * GetGridSize();
	y = row * GetGridSize();

	return true;
}

bool World::AddEntity(Entity* entity)
{
	if (!entity->Initialize())
	{
		return false;
	}

	g_entities.push_back(entity);

	// Whatever they put as the pos, mark it down
	UpdateEntity(entity);

	return true;
}

void World::RemoveEntity(Entity* entity)
{
	g_entityPositions.erase(entity);

	// TODO: We need a linked list or something...
	g_entities.erase(std::remove(g_entities.begin(), g_entities.end(), entity), g_entities.end());
}

void World::UpdateEntity(Entity* entity)
{
	g_entityPositions[entity] = std::make_pair(entity->GetColumn(), entity->GetRow());
}

Entity* World::LookupEntityAtPosition(uint16_t col, uint16_t row)
{
	for (auto& e : g_entityPositions)
	{
		if (e.second.first == col && e.second.second == row)
		{
			return e.first;
		}
	}

	return nullptr;
}

static void RenderGrid()
{
	const SDL_Rect& windowRect = Game::GetWindowRect();

	// SDL_Rect r;
	// r.x = 0;
	// r.y = 0;
	// r.w = windowRect.w;
	// r.h = windowRect.h;

	// SDL_SetRenderDrawColor(Game::GetRenderer(), 197, 234, 243, 255);
	// SDL_RenderFillRect(Game::GetRenderer(), &r);

	// Render the grid lines
	SDL_SetRenderDrawColor(Game::GetRenderer(), 0, 0, 0, 128); // black

	for (int w = 0; w < windowRect.w; w += GRID_SIZE)
	{
		SDL_RenderDrawLine(Game::GetRenderer(), w, 0, w, windowRect.h);

		for (int h = 0; h < windowRect.h; h += GRID_SIZE)
		{
			SDL_RenderDrawLine(Game::GetRenderer(), 0, h, windowRect.w, h);
		}
	}
}

static void RenderGrass()
{
	for (int w = 0; w < Game::GetWindowRect().w; w += GRID_SIZE)
	{
		for (int h = 0; h < Game::GetWindowRect().h; h += GRID_SIZE)
		{
			std::pair<int, int>& rc = GrassTiles[w][h];

			tiles.RenderFrame(w, h, rc.first, rc.second);
		}
	}
}

static void RenderEntities()
{
	// Render walkables first so we can walk over them
	for (auto& e : g_entities)
	{
		WorldEntity* we = dynamic_cast<WorldEntity*>(e);

		if (we && we->Walkable())
		{
			e->Render();
		}
	}

	// Render the rest after
	for (auto& e : g_entities)
	{
		WorldEntity* we = dynamic_cast<WorldEntity*>(e);

		if (we && we->Walkable())
		{
			continue;
		}

		e->Render();
	}
}

void World::Render()
{
	RenderGrass();

	// RenderGrid();

	// Render entities last
	RenderEntities();
}

void World::Tick()
{
	for (auto& e : g_entities)
	{
		e->Tick();
	}
}

static void GenerateGrass(std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>>* grass)
{
	PerlinNoise pn(Random::GetSeed());

	for (int w = 0; w < Game::GetWindowRect().w; w += GRID_SIZE)
	{
		for (int h = 0; h < Game::GetWindowRect().h; h += GRID_SIZE)
		{
			double x = (double)w / ((double)Game::GetWindowRect().w);
			double y = (double)h / ((double)Game::GetWindowRect().h);

			// Typical Perlin noise
			double n = pn.noise(5 * x, 5 * y, 0.8);

			// Wood like structure
			// n = 20 * pn.noise(x, y, 0.8);
			// n = n - floor(n);

			int ground[][2] =
			{
				{ 0, 8 }, // grass short
				{ 1, 8 }, // grass long

				// We should add any other things on top of grass after the fact
				// { 4, 1 }, // flowers
				// { 3, 1 }, // plain
			};

			unsigned count = _countof(ground);
			unsigned noise = static_cast<unsigned>(count * n);
			unsigned col = ground[noise][0];
			unsigned row = ground[noise][1];

			(*grass)[w][h] = std::make_pair(col, row);
		}
	}
}

TextureSprite* World::GetTileSprite(int idx)
{
	// no idx switch atm
	return &tiles;
}

bool World::Initialize()
{
	if (!tiles.Load())
	{
		printf("Unable to load world tiles.\n");

		return false;
	}

	GenerateGrass(&GrassTiles);

	// Need to generate some world items to interact with here, then we need some way for entity to interact...

	return true;
}