#pragma once

#include "WorldEntity.h"

class TreeEntity : public WorldEntity
{
public:
	TreeEntity() = delete;
	TreeEntity(const uint16_t column, const uint16_t row, const uint16_t size) : 
		m_texture(nullptr), m_nextFruitedTime(0u), WorldEntity(column, row, size) {}

	bool Initialize() override;
	void Tick() override;
	void Render() override;
	bool IsReadyForDeletion() override { return false; }
	bool Walkable() override { return false; }
	void OnInteraction(WorldEntity* other, WorldEntityInteraction type) override;

private:

	uint32_t m_nextFruitedTime;
	Texture* m_texture;
};