#pragma once

#include "WorldEntity.h"
#include "NeuralEntity.h"

class PlayerEntity : public WorldEntity
{
	static constexpr float MinimumSpeed = 0.5f;
	static constexpr float MaximumSpeed = 1.0f;

public:
	PlayerEntity() = delete;
	PlayerEntity(const SDL_Color& color, const uint16_t col, const uint16_t row, const uint16_t size) :
		m_color(color), m_sprite(nullptr),
		m_idleDownAnim(nullptr), m_idleLeftAnim(nullptr), m_idleRightAnim(nullptr), m_idleUpAnim(nullptr),
		m_movingDownAnim(nullptr), m_movingLeftAnim(nullptr), m_movingRightAnim(nullptr), m_movingUpAnim(nullptr),
		m_anim(nullptr), m_currentAnimShard(nullptr), m_health(1.0f), m_hunger(0.0f), m_thirst(0.0f), m_speed(1.0f),
		m_neuralEnt(nullptr),
		WorldEntity(col, row, size) {}

	bool Initialize() override;
	void Tick() override;
	void Render() override;
	bool Walkable() override { return false; }
	void Interact(WorldEntity* other, WorldEntityInteraction type) override;
	void OnInteraction(WorldEntity* other, WorldEntityInteraction type) override;

	// void LookLeft() override;
	// void LookRight() override;
	// void LookUp() override;
	// void LookDown() override;

	bool MoveLeft() override;
	bool MoveRight() override;
	bool MoveUp() override;
	bool MoveDown() override;

	bool IsMoving() override;
	bool IsIdle() override;

	float GetHealth() const { return m_health; }
	float GetHunger() const { return m_hunger; }
	float GetThirst() const { return m_thirst; }
	float GetSpeed() const { return m_speed; }

	void SetHealth(float health) { m_health = health; }
	void SetHunger(float hunger) { m_hunger = hunger; }
	void SetThirst(float thirst) { m_thirst = thirst; }
	void SetSpeed(float speed) { m_speed = speed; }
	
	bool CanReach(uint16_t col, uint16_t row);
	bool CanMove(uint16_t col, uint16_t row);

private:
	void SetAnimationShard(AnimationShard* shard);
	void SetAnimationForDirection();

	// Color
	SDL_Color m_color;

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