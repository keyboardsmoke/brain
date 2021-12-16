#include "WaterEntity.h"
#include "World.h"
#include "TextureSprite.h"
#include "Random.h"
#include "PlayerEntity.h"
#include "Game.h"

bool WaterEntity::Initialize()
{
	m_sprite = new TextureSprite("../Resources/water_shimmer.png", 16);

	if (!m_sprite || !m_sprite->Load())
	{
		return false;
	}

	m_anim = new Animation(m_sprite);

	if (!m_anim)
	{
		return false;
	}

	m_currentAnimShard = m_anim->CreateShard();
	m_currentAnimShard->AddStage(0, 0, 500);
	m_currentAnimShard->AddStage(0, 1, 500);

	return true;
}

void WaterEntity::Tick()
{
	if (m_currentAnimShard != nullptr)
	{
		m_currentAnimShard->Tick();
	}
}

void WaterEntity::Render()
{
	// We don't render anim here, and we don't set an animation for water
	// because it's a multi-layered thing. It's weird and annoying.
	SDL_SetRenderDrawColor(Game::GetRenderer(), 89, 125, 206, 255);

	SDL_Rect waterRect = 
	{ 
		GetPositionX(), 
		GetPositionY(), 
		static_cast<int>(World::GetGridSize()), 
		static_cast<int>(World::GetGridSize()) 
	};

	SDL_RenderFillRect(Game::GetRenderer(), &waterRect);

	m_currentAnimShard->Render(GetPositionX(), GetPositionY());
}

void WaterEntity::Interact(Entity* other)
{
	if (PlayerEntity* p = dynamic_cast<PlayerEntity*>(other))
	{
		// Eliminate it, unlike food this is a lake we're talking about
		// They'll likely immediately be cured of thirst
		p->SetThirst(0.0f);
	}
}