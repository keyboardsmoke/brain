#pragma once

#include <unordered_map>

class Entity;
class TextureSprite;

class World
{
public:
	static uint32_t GetGridSize();
	static void GetGridDims(uint16_t& cols, uint16_t& rows);
	static uint16_t GetGridMaxColumns();
	static uint16_t GetGridMaxRows();
	static bool IsValidGridPosition(uint16_t col, uint16_t row);
	static bool GetGridFromPos(uint16_t x, uint16_t y, uint16_t& col, uint16_t& row);
	static bool GetPosFromGrid(uint16_t col, uint16_t row, uint16_t& x, uint16_t& y);

	static bool AddEntity(Entity* entity);
	static void RemoveEntity(Entity* entity);
	static void UpdateEntity(Entity* entity);
	static std::vector<Entity*>& GetEntities();
	static Entity* LookupEntityAtPosition(uint16_t col, uint16_t row);

	static bool Initialize();
	static void Tick();
	static void Render();
};