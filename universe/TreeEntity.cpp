#include "TreeEntity.h"
#include "Game.h"

bool TreeEntity::Initialize()
{
	m_texture = new Texture("../Resources/tree.png");

	if (!m_texture || !m_texture->Load())
	{
		return false;
	}

	return true;
}

void TreeEntity::Tick()
{
	/*
	Uint32 nextTime = m_nextFruitedTime = SDL_GetTicks() + 3600;

	if (m_nextFruitedTime == 0u)
	{
		// some point in the future, we make da fruit
		m_nextFruitedTime = nextTime;
	}

	if (SDL_GetTicks() > m_nextFruitedTime)
	{
		m_nextFruitedTime = nextTime;
	}*/
}

void TreeEntity::Render()
{
	m_texture->Render(GetCoordX(), GetCoordY());
}

void TreeEntity::OnInteraction(WorldEntity* other, WorldEntityInteraction type)
{
	//
}