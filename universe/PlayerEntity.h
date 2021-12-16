#pragma once

#include "WorldEntity.h"
#include "NeuralEntity.h"

class PlayerEntity : public WorldEntity
{
	static constexpr float MinimumSpeed = 0.5f;
	static constexpr float MaximumSpeed = 1.0f;

public:
	PlayerEntity() = delete;
	PlayerEntity(uint16_t col, uint16_t row) :
		WorldEntity(col, row) {}

	bool Initialize() override;
	void Tick() override;
	void Render() override;
	bool Walkable() override { return false; }
	void Interact(Entity* other) override;

	// void LookLeft() override;
	// void LookRight() override;
	// void LookUp() override;
	// void LookDown() override;

	void MoveLeft() override;
	void MoveRight() override;
	void MoveUp() override;
	void MoveDown() override;

	bool IsMoving();
	bool IsIdle();

	float GetHealth() const { return m_health; }
	float GetHunger() const { return m_hunger; }
	float GetThirst() const { return m_thirst; }
	float GetSpeed() const { return m_speed; }

	void SetHealth(float health) { m_health = health; }
	void SetHunger(float hunger) { m_hunger = hunger; }
	void SetThirst(float thirst) { m_thirst = thirst; }
	void SetSpeed(float speed) { m_speed = speed; }

private:
	void SetAnimationForDirection(Direction dir);

	// TextureSprite as a basis for the animations below
	TextureSprite* m_sprite;

	// Loaded animations
	AnimationShard* m_idleDownAnim;
	AnimationShard* m_idleLeftAnim;
	AnimationShard* m_idleRightAnim;
	AnimationShard* m_idleUpAnim;

	AnimationShard* m_movingDownAnim;
	AnimationShard* m_movingLeftAnim;
	AnimationShard* m_movingRightAnim;
	AnimationShard* m_movingUpAnim;

	// Current animation
	Animation* m_anim;
	AnimationShard* m_currentAnimShard;

	// living state of the "players" aka the simulated entities
	// Since we don't have actual biological processes, we just have to sort of... do this
	// I think these will end up being fed into sensory neurons, if in a different form
	float m_health;
	float m_hunger;
	float m_thirst;
	float m_speed;

	// The brain business that will control the player
	NeuralEntity* m_neuralEnt;
};