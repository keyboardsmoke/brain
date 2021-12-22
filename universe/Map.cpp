#include "Map.h"
#include <lodepng.h>

bool Map::Load()
{
	std::vector<uint8_t> buffer;
	if (lodepng::load_file(buffer, m_filename) != 0)
	{
		return false;
	}

	std::vector<uint8_t> outBuffer;
	if (lodepng::decode(outBuffer, m_width, m_height, buffer) != 0)
	{
		return false;
	}

	uint32_t numPixels = m_width * m_height; // or outBuffer size, really...

	printf("Map Width [%d] Height [%d]\n", m_width, m_height);

	for (uint32_t i = 0; i < numPixels; i += sizeof(uint32_t))
	{
		uint32_t color = *(uint32_t*)&outBuffer.data()[i];

		switch (color)
		{
		case 0xff000000:
			printf("Tree at [%d]\n", i);
			m_values[i] = EntityType::Tree;
			break;
		case 0xffffffff:
			printf("Water at [%d]\n", i);
			m_values[i] = EntityType::Water;
			break;
		case 0:
			// don't do anything, no data
			break;
		default:
			printf("Unsupport entity type at [%d] color = 0x%x\n", i, color);
			break;
		}
	}

	return true;
}