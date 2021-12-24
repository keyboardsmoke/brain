#include "FoodEntity.h"
#include "Game.h"
#include "TextureCache.h"
#include "Random.h"

bool FoodEntity::Initialize()
{
	m_sprite = new TextureSprite("../Resources/fruit.png", 16);

	if (!m_sprite || !m_sprite->Load())
	{
		return false;
	}

	uint16_t numCols = m_sprite->GetTexture()->GetTextureWidth() / World::GetGridSize();
	uint16_t numRows = m_sprite->GetTexture()->GetTextureHeight() / World::GetGridSize();

	m_foodCol = Random::Integer<uint16_t>(0, numCols);
	m_foodRow = Random::Integer<uint16_t>(0, numRows);

	return true;
}

void FoodEntity::Render()
{
	m_sprite->RenderFrame(GetCoordX(), GetCoordY(), m_foodCol, m_foodRow);
}

void FoodEntity::OnInteraction(WorldEntity* other, WorldEntityInteraction type)
{
	//
}