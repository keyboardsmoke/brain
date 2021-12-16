#pragma once

#include "WorldEntity.h"
#include "Timer.h"

class WaterEntity : public WorldEntity
{
public:
	WaterEntity() : m_sprite(nullptr), m_anim(nullptr), m_currentAnimShard(nullptr), WorldEntity() {}
	WaterEntity(const uint16_t column, const uint16_t row) : m_sprite(nullptr), m_anim(nullptr), m_currentAnimShard(nullptr), WorldEntity(column, row) {}

	bool Initialize() override;
	void Tick() override;
	void Render() override;
	bool Walkable() override { return false; }
	void Interact(Entity* other) override;

private:

	// TextureSprite as a basis for the animations below
	TextureSprite* m_sprite;

	// Current animation
	Animation* m_anim;
	AnimationShard* m_currentAnimShard;
};