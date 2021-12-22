#include "Mouse.h"
#include "World.h"
#include "sdl_includes.h"

bool Mouse::GetPosition(uint16_t& col, uint16_t& row)
{
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);
	return World::GetGridFromPos(x, y, col, row);
}

bool Mouse::IsOver(uint16_t col, uint16_t row)
{
	uint16_t mc = 0, mr = 0;
	if (GetPosition(mc, mr))
	{
		return (mc == col && mr == row);
	}

	return false;
}