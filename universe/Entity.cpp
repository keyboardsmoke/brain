#include "Entity.h"
#include "World.h"

void Entity::GetAbsolutePosition(uint16_t& x, uint16_t& y)
{
	x = m_column * World::GetGridSize();
	y = m_row * World::GetGridSize();
}