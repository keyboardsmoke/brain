#pragma once

#include <cstdint>
#include <optional>

#include "2DTypes.h"
#include "Animation.h"
#include "World.h"

class Entity
{
public:
	Entity() : m_column(0u), m_row(0u), m_size(1u) {}
	Entity(const uint16_t column, const uint16_t row, const uint16_t size) : m_column(column), m_row(row), m_size(size) {}

	// Initialization for the entity, generally when it's being created
	virtual bool Initialize() { return true; }

	// Tick function for the entity
	virtual void Tick() { }

	// Render function for the entity
	// This makes batch rendering impossible, which does kind of suck.
	// Might need to rework this for some things, instead of "water" entities, 
	// there's a "lake" entity that does efficient fills/draws
	virtual void Render() = 0;

	void GetAbsolutePosition(uint16_t& x, uint16_t& y);
	
	uint16_t GetColumn() const { return m_column; }
	void SetColumn(uint16_t col) { m_column = col; }

	uint16_t GetRow() const { return m_row; }
	void SetRow(uint16_t row) { m_row = row; }

	uint16_t GetSize() const { return m_size; }
	void SetSize(uint16_t size) { m_size = size; }

	//
	Rect2D<uint16_t> GetRawDims()
	{
		return { GetCoordX(), GetCoordY(), GetCoordWidth(), GetCoordHeight() };
	}

	Rect2D<uint16_t> GetDims()
	{
		return { m_column, m_row, m_size, m_size };
	}

protected:
	// Unsafe and without checks, but faster and easier to use
	uint16_t GetCoordX() { return m_column * World::GetGridSize(); }
	uint16_t GetCoordY() { return m_row * World::GetGridSize(); }

	// 
	uint16_t GetCoordWidth() { return m_size * World::GetGridSize(); }
	uint16_t GetCoordHeight() { return m_size * World::GetGridSize(); }

	Point2D<uint16_t> GetPosition() { return Point2D<uint16_t>(GetCoordX(), GetCoordY()); }

	// Rather than absolute position, just store these. It'll be easier.
	uint16_t m_column;
	uint16_t m_row;

	// How many grid positions does this entity take up?...
	uint16_t m_size;
};