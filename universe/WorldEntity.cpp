#include "WorldEntity.h"

bool WorldEntity::MoveLeft()
{
	if (GetColumn() == 0u)
		return false;

	if (CanMove(GetColumn() - 1, GetRow()))
	{
		LookLeft();

		SetColumn(GetColumn() - 1);

		World::UpdateEntity(this);

		return true;
	}

	return false;
}

bool WorldEntity::MoveRight()
{
	if (GetColumn() == World::GetGridMaxColumns())
		return false;

	if (CanMove(GetColumn() + 1, GetRow()))
	{
		LookRight();

		SetColumn(GetColumn() + 1);

		World::UpdateEntity(this);

		return true;
	}

	return false;
}

bool WorldEntity::MoveUp()
{
	if (GetRow() == 0u)
		return false;

	if (CanMove(GetColumn(), GetRow() - 1))
	{
		LookUp();

		SetRow(GetRow() - 1);

		World::UpdateEntity(this);

		return true;
	}

	return false;
}

bool WorldEntity::MoveDown()
{
	if (GetRow() == World::GetGridMaxRows())
		return false;

	if (CanMove(GetColumn(), GetRow() + 1))
	{
		LookDown();

		SetRow(GetRow() + 1);

		World::UpdateEntity(this);

		return true;
	}

	return false;
}

bool WorldEntity::IsMoving()
{
	return false; // return (!m_movementTimer.IsStarted() || (m_movementTimer.IsStarted() && m_movementTimer.IsFinished()));
}

bool WorldEntity::IsIdle()
{
	return !IsMoving();
}

bool WorldEntity::CanMove(uint16_t col, uint16_t row)
{
	return World::IsValidGridPosition(col, row);
}