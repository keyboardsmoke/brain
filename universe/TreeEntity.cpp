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

void TreeEntity::Render()
{
	m_texture->Render(GetCoordX(), GetCoordY());
}

void TreeEntity::OnInteraction(WorldEntity* other, WorldEntityInteraction type)
{
	//
}