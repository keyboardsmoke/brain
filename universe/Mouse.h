#pragma once

#include <cstdint>

class Mouse
{
public:
	static bool GetPosition(uint16_t& col, uint16_t& row);
	static bool IsOver(uint16_t col, uint16_t row);
};