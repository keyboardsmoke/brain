#pragma once

#include "WorldEntity.h"

class TreeEntity : public WorldEntity
{
public:
	TreeEntity() = delete;
	TreeEntity(const uint16_t column, const uint16_t row, const uint16_t size) : m_texture(nullptr), WorldEntity(column, row, size) {}

	bool Initialize() override;
	void Render() override;
	bool Walkable() override { return false; }
	void OnInteraction(WorldEntity* other, WorldEntityInteraction type) override;

private:
	Texture* m_texture;
};