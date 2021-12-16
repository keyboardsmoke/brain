#pragma once

#include <cstdint>
#include <optional>

#include "2DTypes.h"
#include "Animation.h"
#include "World.h"

class Entity
{
public:
	Entity() : m_column(0u), m_row(0u) {}
	Entity(const uint16_t column, const uint16_t row) : m_column(column), m_row(row) {}

	// Initialization for the entity, generally when it's being created
	virtual bool Initialize() { return true; }

	// Tick function for the entity
	virtual void Tick() = 0;

	// Render function for the entity
	// This makes batch rendering impossible, which does kind of suck.
	// Might need to rework this for some things, instead of "water" entities, 
	// there's a "lake" entity that does efficient fills/draws
	virtual void Render() = 0;

	void GetAbsolutePosition(uint16_t& x, uint16_t& y);
	uint16_t GetColumn() const { return m_column; }
	uint16_t GetRow() const { return m_row; }

protected:
	// Unsafe and without checks, but faster and easier to use
	uint16_t GetPositionX() { return m_column * World::GetGridSize(); }
	uint16_t GetPositionY() { return m_row * World::GetGridSize(); }

	// Rather than absolute position, just store these. It'll be easier.
	uint16_t m_column;
	uint16_t m_row;
};