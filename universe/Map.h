#pragma once

#include <string>
#include <map>
#include <tuple>

class Map
{
public:
	enum class EntityType
	{
		None,
		Water,
		Tree
	};

	Map() = delete;
	Map(const std::string& filename) : m_filename(filename), m_width(0u), m_height(0u), m_values() {}

	bool Load();

	uint32_t GetWidth() const { return m_width; }
	uint32_t GetHeight() const { return m_height; }

	std::map<std::pair<int, int>, EntityType>& GetValues() { return m_values; }

private:
	std::string m_filename;
	uint32_t m_width;
	uint32_t m_height;

	std::map<std::pair<int, int>, EntityType> m_values;
};