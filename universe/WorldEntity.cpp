#include "WorldEntity.h"

static bool CanMove(uint16_t currentCol, uint16_t currentRow, uint16_t newCol, uint16_t newRow)
{
	Entity* existingEntity = World::LookupEntityAtPosition(newCol, newRow);

	if (WorldEntity* we = dynamic_cast<WorldEntity*>(existingEntity))
	{
		if (we->Walkable() == false)
		{
			return false;
		}
	}

	return true;
}

void WorldEntity::MoveLeft()
{
	LookLeft();

	if (m_column == 0u)
		return;

	if (CanMove(m_column, m_row, m_column - 1, m_row))
	{
		--m_column;

		World::UpdateEntity(this);
	}
}

void WorldEntity::MoveRight()
{
	LookRight();

	if (m_column == World::GetGridMaxColumns())
		return;

	if (CanMove(m_column, m_row, m_column + 1, m_row))
	{
		++m_column;

		World::UpdateEntity(this);
	}
}

void WorldEntity::MoveUp()
{
	LookUp();

	if (m_row == 0u)
		return;

	if (CanMove(m_column, m_row, m_column, m_row - 1))
	{
		--m_row;

		World::UpdateEntity(this);
	}
}

void WorldEntity::MoveDown()
{
	LookDown();

	if (m_row == World::GetGridMaxRows())
		return;

	if (CanMove(m_column, m_row, m_column, m_row + 1))
	{
		++m_row;

		World::UpdateEntity(this);
	}
}