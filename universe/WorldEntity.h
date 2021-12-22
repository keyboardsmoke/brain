#pragma once

#include "2DTypes.h"
#include "Timer.h"
#include "Entity.h"

// World entities are just anything that exists in the world that can be interacted with

enum class WorldEntityInteraction
{
	DRINK,
	EAT,
	TALK,
	ATTACK,
};

class WorldEntity : public Entity
{
public:
	WorldEntity() : m_direction(Direction::DOWN), Entity() {}
	WorldEntity(const uint16_t column, const uint16_t row, const uint16_t size) : m_direction(Direction::DOWN), Entity(column, row, size) {}

	// Do something when something interacts with you
	virtual void OnInteraction(WorldEntity* other, WorldEntityInteraction type) = 0;

	// Do something when something to interact with another
	virtual void Interact(WorldEntity* other, WorldEntityInteraction type) 
	{ 
		other->OnInteraction(this, type); 
	}

	// Return true if this entity does not collide
	virtual bool Walkable() = 0;

	virtual void LookLeft() { m_direction = Direction::LEFT; }
	virtual void LookRight() { m_direction = Direction::RIGHT; }
	virtual void LookUp() { m_direction = Direction::UP; }
	virtual void LookDown() { m_direction = Direction::DOWN; }

	// Ticks is the amount of time it takes to reach the destination
	// The entity then moves at the destination at that speed
	// This is meant to sync with animations, though not explicitly tied to it
	// 0 ticks = instant movement
	virtual bool MoveLeft();
	virtual bool MoveRight();
	virtual bool MoveUp();
	virtual bool MoveDown();

	// Is the entity currently changing it's position in space
	// Movement speed is derived from animation speed... ?
	virtual bool IsMoving();

	// Is the entity "still"
	virtual bool IsIdle();

	// Just assume we can move anywhere without collision
	virtual bool CanMove(uint16_t col, uint16_t row);

protected:
	Direction m_direction;
};