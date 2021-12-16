#include "PlayerEntity.h"
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
	m_idleDownAnim->Reset();

	m_idleLeftAnim->AddStage(1, 1, 1000);
	m_idleLeftAnim->Reset();

	m_idleRightAnim->AddStage(1, 2, 1000);
	m_idleRightAnim->Reset();

	m_idleUpAnim->AddStage(1, 3, 1000);
	m_idleUpAnim->Reset();

	m_movingDownAnim = m_anim->CreateShard();
	m_movingLeftAnim = m_anim->CreateShard();
	m_movingRightAnim = m_anim->CreateShard();
	m_movingUpAnim = m_anim->CreateShard();

	m_movingDownAnim->AddStage(0, 0, 300);
	m_movingDownAnim->AddStage(1, 0, 300);
	m_movingDownAnim->AddStage(2, 0, 300);
	m_movingDownAnim->Reset();

	m_movingLeftAnim->AddStage(0, 1, 300);
	m_movingLeftAnim->AddStage(1, 1, 300);
	m_movingLeftAnim->AddStage(2, 1, 300);
	m_movingLeftAnim->Reset();

	m_movingRightAnim->AddStage(0, 2, 300);
	m_movingRightAnim->AddStage(1, 2, 300);
	m_movingRightAnim->AddStage(2, 2, 300);
	m_movingRightAnim->Reset();

	m_movingUpAnim->AddStage(0, 3, 300);
	m_movingUpAnim->AddStage(1, 3, 300);
	m_movingUpAnim->AddStage(2, 3, 300);
	m_movingUpAnim->Reset();

	m_currentAnimShard = m_idleDownAnim;
	// m_currentAnimShard = m_movingDownAnim;

	return true;
}

void PlayerEntity::Tick()
{
	// Ever increasing
	// m_hunger += 0.05f;
	// m_thirst += 0.02f;

	// m_speed = SSE::clamp(1.0f - (m_hunger + m_thirst), PlayerEntity::MinimumSpeed, PlayerEntity::MaximumSpeed);
}

void PlayerEntity::Render()
{
	m_currentAnimShard->Render(GetPositionX(), GetPositionY());
}

void PlayerEntity::Interact(Entity* other)
{

}

static void SetMoveDirectionAnim(AnimationShard* anim, AnimationShard* newStateMovingAnim, AnimationShard* newStateIdleAnim)
{
	// For some reason it's not playing the animations?...

	anim = newStateMovingAnim;
	anim->Reset();
	anim->SetCallback([](AnimationShard* anim, void* userdata) -> void
	{
		anim = reinterpret_cast<AnimationShard*>(userdata);
	}, newStateIdleAnim);
}

void PlayerEntity::MoveLeft()
{
	SetAnimationForDirection(Direction::LEFT);

	WorldEntity::MoveLeft();
}

void PlayerEntity::MoveRight()
{
	SetAnimationForDirection(Direction::RIGHT);

	WorldEntity::MoveRight();
}

void PlayerEntity::MoveUp()
{
	SetAnimationForDirection(Direction::UP);

	WorldEntity::MoveUp();
}

void PlayerEntity::MoveDown()
{
	SetAnimationForDirection(Direction::DOWN);

	WorldEntity::MoveDown();
}

bool PlayerEntity::IsMoving()
{
	return (
		m_currentAnimShard == m_movingDownAnim ||
		m_currentAnimShard == m_movingLeftAnim ||
		m_currentAnimShard == m_movingRightAnim ||
		m_currentAnimShard == m_movingUpAnim
		);
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

void PlayerEntity::SetAnimationForDirection(Direction dir)
{
	switch (dir)
	{
	case Direction::DOWN:
		SetMoveDirectionAnim(m_currentAnimShard, m_movingDownAnim, m_idleDownAnim);
		break;
	case Direction::LEFT:
		SetMoveDirectionAnim(m_currentAnimShard, m_movingLeftAnim, m_idleLeftAnim);
		break;
	case Direction::RIGHT:
		SetMoveDirectionAnim(m_currentAnimShard, m_movingRightAnim, m_idleRightAnim);
		break;
	case Direction::UP:
		SetMoveDirectionAnim(m_currentAnimShard, m_movingUpAnim, m_idleUpAnim);
		break;
	}
}