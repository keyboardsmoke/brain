#include "PlayerEntity.h"
#include "World.h"
#include "Mouse.h"
#include "SSE.h"

struct AnimationCbData
{
	Animation* m_anim;
};

bool PlayerEntity::Initialize()
{
	m_sprite = new TextureSprite("../Resources/blob_white.png", 16);

	if (!m_sprite || !m_sprite->Load())
	{
		return false;
	}

	m_anim = new Animation(m_sprite);

	if (!m_anim)
	{
		return false;
	}

	m_idleDownAnim = m_anim->CreateShard();
	m_idleLeftAnim = m_anim->CreateShard();
	m_idleRightAnim = m_anim->CreateShard();
	m_idleUpAnim = m_anim->CreateShard();

	m_idleDownAnim->AddStage(1, 0, 1000);
	m_idleLeftAnim->AddStage(1, 1, 1000);
	m_idleRightAnim->AddStage(1, 2, 1000);

	m_idleUpAnim->AddStage(1, 3, 1000);

	m_movingDownAnim = m_anim->CreateShard();
	m_movingLeftAnim = m_anim->CreateShard();
	m_movingRightAnim = m_anim->CreateShard();
	m_movingUpAnim = m_anim->CreateShard();

	m_movingDownAnim->AddStage(0, 0, 200);
	m_movingDownAnim->AddStage(1, 0, 200);
	m_movingDownAnim->AddStage(2, 0, 200);
	m_movingDownAnim->SetCallback([&](AnimationShard* anim, void* userdata) -> void
	{
		m_currentAnimShard = m_idleDownAnim;
		m_currentAnimShard->Reset();
	});

	m_movingLeftAnim->AddStage(0, 1, 200);
	m_movingLeftAnim->AddStage(1, 1, 200);
	m_movingLeftAnim->AddStage(2, 1, 200);
	m_movingLeftAnim->SetCallback([&](AnimationShard* anim, void* userdata) -> void
	{
		m_currentAnimShard = m_idleLeftAnim;
		m_currentAnimShard->Reset();
	});

	m_movingRightAnim->AddStage(0, 2, 200);
	m_movingRightAnim->AddStage(1, 2, 200);
	m_movingRightAnim->AddStage(2, 2, 200);
	m_movingRightAnim->SetCallback([&](AnimationShard* anim, void* userdata) -> void
	{
		m_currentAnimShard = m_idleRightAnim;
		m_currentAnimShard->Reset();
	});

	m_movingUpAnim->AddStage(0, 3, 200);
	m_movingUpAnim->AddStage(1, 3, 200);
	m_movingUpAnim->AddStage(2, 3, 200);
	m_movingUpAnim->SetCallback([&](AnimationShard* anim, void* userdata) -> void
	{
		m_currentAnimShard = m_idleUpAnim;
		m_currentAnimShard->Reset();
	});

	m_currentAnimShard = m_idleDownAnim;
	// m_currentAnimShard = m_movingDownAnim;

	return true;
}

void PlayerEntity::Tick()
{
	if (m_currentAnimShard != nullptr)
	{
		m_currentAnimShard->Tick();
	}
}

static Point2D<float> GetLastPositionForDirection(Direction dir, const Point2D<float>& pos)
{
	Point2D<float> value(0.0f, 0.0f);

	float nx = pos.x;
	float ny = pos.y;

	switch (dir)
	{
	case Direction::UP: value.x = nx; value.y = ny + World::GetGridSize(); break;
	case Direction::DOWN: value.x = nx; value.y = ny - World::GetGridSize(); break;
	case Direction::LEFT: value.x = nx + World::GetGridSize(); value.y = ny; break;
	case Direction::RIGHT: value.x = nx - World::GetGridSize(); value.y = ny; break;
	}

	return value;
}

void PlayerEntity::Render()
{
	// Color modulation to give skin color
	SDL_SetTextureColorMod(m_sprite->GetTexture()->GetSDLTexture(), m_color.r, m_color.g, m_color.b);

	// We have to do a trick here to render the entity moving, in a tile based system
	// We basically have a fake x/y, but under the hood the units are still col/row
	// The entity is just _rendered_ at a delta location

	if (IsMoving())
	{
		// next x/y (current "real" position)
		Point2D<float> posf(static_cast<float>(GetCoordX()), static_cast<float>(GetCoordY()));
		Point2D<float> dp = GetLastPositionForDirection(m_direction, Point2D<float>(GetCoordX(), GetCoordY()));

		// with src and dst, we can calculate where the anim is supposed to be playing based on how much the anim is finished...
		uint32_t doneTicks = m_currentAnimShard->GetTotalTicks() - m_currentAnimShard->GetRemainingTicks();

		// 50 out of 100 = 0.5
		float doneFrac = static_cast<float>(doneTicks) / static_cast<float>(m_currentAnimShard->GetTotalTicks());

		float fx = dp.x + ((posf.x - dp.x) * doneFrac);
		float fy = dp.y + ((posf.y - dp.y) * doneFrac);

		m_currentAnimShard->Render(static_cast<int>(fx), static_cast<int>(fy), GetCoordWidth(), GetCoordHeight());
	}
	else
	{
		m_currentAnimShard->Render(GetCoordX(), GetCoordY(), GetCoordWidth(), GetCoordHeight());
	}
}

void PlayerEntity::Interact(WorldEntity* other, WorldEntityInteraction type)
{
	WorldEntity::Interact(other, type);

	// Switch type, do stuff
	//
}

void PlayerEntity::OnInteraction(WorldEntity* other, WorldEntityInteraction type)
{
	// Something has interacted with me, in what way?
	// I'm not sure we can even quantify "relationships" here
	// So what happens to a player is probably random? idk.

	// Switch type, do stuff
}

bool PlayerEntity::MoveLeft()
{
	const bool m = WorldEntity::MoveLeft();

	if (m)
	{
		SetAnimationForDirection();
	}

	return m;
}

bool PlayerEntity::MoveRight()
{
	const bool m = WorldEntity::MoveRight();

	if (m)
	{
		SetAnimationForDirection();
	}

	return m;
}

bool PlayerEntity::MoveUp()
{
	const bool m = WorldEntity::MoveUp();

	if (m)
	{
		SetAnimationForDirection();
	}

	return m;
}

bool PlayerEntity::MoveDown()
{
	const bool m = WorldEntity::MoveDown();

	if (m)
	{
		SetAnimationForDirection();
	}

	return m;
}

bool PlayerEntity::IsMoving()
{
	const bool movingAnim = (
		m_currentAnimShard == m_movingDownAnim ||
		m_currentAnimShard == m_movingLeftAnim ||
		m_currentAnimShard == m_movingRightAnim ||
		m_currentAnimShard == m_movingUpAnim
		);

	return (movingAnim && m_currentAnimShard->GetRemainingTicks() != 0);
}

bool PlayerEntity::IsIdle()
{
	return (
		m_currentAnimShard == m_idleDownAnim ||
		m_currentAnimShard == m_idleLeftAnim ||
		m_currentAnimShard == m_idleRightAnim ||
		m_currentAnimShard == m_idleUpAnim
		);
}

bool PlayerEntity::CanReach(uint16_t col, uint16_t row)
{
	if (!World::IsValidGridPosition(col, row))
		return false;

	if (((GetColumn() - 1) == col && row == GetRow()) ||
		((GetColumn() + 1) == col && row == GetRow()) ||
		(GetColumn() == col && (GetRow() - 1) == row) ||
		(GetColumn() == col && (GetRow() + 1) == row))
	{
		// We can interact with this
		return true;
	}

	return false;
}

bool PlayerEntity::CanMove(uint16_t col, uint16_t row)
{
	// If we can't reach it, we sure can't move there
	// if (!CanReach(col, row)) return false;

	Entity* existingEntity = World::LookupEntityAtPosition(col, row);

	// TODO: Error, can't find the entity?...

	if (WorldEntity* we = dynamic_cast<WorldEntity*>(existingEntity))
	{
		if (we->Walkable() == false)
		{
			return false;
		}
	}

	return WorldEntity::CanMove(col, row);
}

void PlayerEntity::SetAnimationShard(AnimationShard* shard)
{
	// Don't bother
//	if (m_currentAnimShard == shard)
//		return;

	shard->Reset();

	m_currentAnimShard = shard;
}

void PlayerEntity::SetAnimationForDirection()
{
	switch (m_direction)
	{
	case Direction::DOWN:
		SetAnimationShard(m_movingDownAnim);
		break;
	case Direction::LEFT:
		SetAnimationShard(m_movingLeftAnim);
		break;
	case Direction::RIGHT:
		SetAnimationShard(m_movingRightAnim);
		break;
	case Direction::UP:
		SetAnimationShard(m_movingUpAnim);
		break;
	}
}