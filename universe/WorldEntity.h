#pragma once

#include "2DTypes.h"
#include "Entity.h"

// World entities are just anything that exists in the world that can be interacted with

class WorldEntity : public Entity
{
public:
	WorldEntity() : m_direction(Direction::DOWN), Entity() {}
	WorldEntity(const uint16_t column, const uint16_t row) : m_direction(Direction::DOWN), Entity(column, row) {}

	// Do something when something interacts with you
	virtual void Interact(Entity* other) = 0;

	// Return true if this entity does not collide
	virtual bool Walkable() = 0;

	virtual void LookLeft() { m_direction = Direction::LEFT; }
	virtual void LookRight() { m_direction = Direction::RIGHT; }
	virtual void LookUp() { m_direction = Direction::UP; }
	virtual void LookDown() { m_direction = Direction::DOWN; }

	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void MoveUp();
	virtual void MoveDown();

protected:
	Direction m_direction;
};