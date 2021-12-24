#pragma once

#include "WorldEntity.h"

class FoodEntity : public WorldEntity
{
public:
	FoodEntity() = delete;
	FoodEntity(const uint16_t column, const uint16_t row, const uint16_t size) : 
		m_sprite(nullptr), m_foodCol(0u), m_foodRow(0u), WorldEntity(column, row, size) {}

	bool Initialize() override;
	void Render() override;
	bool IsReadyForDeletion() override { return false; }
	bool Walkable() override { return false; }
	void OnInteraction(WorldEntity* other, WorldEntityInteraction type) override;

private:
	TextureSprite* m_sprite;

	uint16_t m_foodCol;
	uint16_t m_foodRow;
};