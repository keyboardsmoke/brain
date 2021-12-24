#pragma once

#include "WorldEntity.h"
#include "NeuralEntity.h"

class PlayerEntity : public WorldEntity
{
	static constexpr uint32_t DeathFadeTime = 5000;

public:
	PlayerEntity() = delete;
	PlayerEntity(const SDL_Color& color, const uint16_t col, const uint16_t row, const uint16_t size) :
		m_color(color), m_sprite(nullptr), m_deadSprite(nullptr),
		m_idleDownAnim(nullptr), m_idleLeftAnim(nullptr), m_idleRightAnim(nullptr), m_idleUpAnim(nullptr),
		m_movingDownAnim(nullptr), m_movingLeftAnim(nullptr), m_movingRightAnim(nullptr), m_movingUpAnim(nullptr),
		m_anim(nullptr), m_currentAnimShard(nullptr), m_dead(false), m_deadTick(0u), m_bornTick(SDL_GetTicks()),
		m_health(1.0f), m_hunger(0.0f), m_thirst(0.0f), m_speed(1.0f),
		m_neuralEnt(nullptr),
		WorldEntity(col, row, size) {}

	~PlayerEntity() override
	{
		printf("PlayerEntity delete...\n");
	}

	bool Initialize() override;
	void Tick() override;
	void Render() override;
	bool IsReadyForDeletion() override;
	bool Walkable() override { return false; }
	void Interact(WorldEntity* other, WorldEntityInteraction type) override;
	void OnInteraction(WorldEntity* other, WorldEntityInteraction type) override;

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
	const SDL_Color& GetColor() const { return m_color; }
	Uint8 GetColorR() const { return m_color.r; }
	Uint8 GetColorG() const { return m_color.g; }
	Uint8 GetColorB() const { return m_color.b; }
	Uint8 GetColorA() const { return m_color.a; }
	NeuralEntity* GetNeuralEntity() { return m_neuralEnt; }

	void SetHealth(float health) { m_health = health; }
	void SetHunger(float hunger) { m_hunger = hunger; }
	void SetThirst(float thirst) { m_thirst = thirst; }
	void SetSpeed(float speed) { m_speed = speed; }
	void SetColor(SDL_Color color) { m_color = color; }
	void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { m_color.r = r; m_color.g = g; m_color.b = b; m_color.a = a; }
	void SetNeuralEntity(NeuralEntity* nent) { m_neuralEnt = nent; }

	bool CanReach(uint16_t col, uint16_t row);
	bool CanMove(uint16_t col, uint16_t row);

	void Die();

private:
	void SetAnimationShard(AnimationShard* shard);
	void SetAnimationForDirection();

	// Color
	SDL_Color m_color;

	// TextureSprite as a basis for the animations below
	TextureSprite* m_sprite;
	TextureSprite* m_deadSprite;

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
	bool m_dead;
	uint32_t m_deadTick;
	uint32_t m_bornTick;

	float m_health;
	float m_hunger;
	float m_thirst;
	float m_speed;

	// The brain business that will control the player
	NeuralEntity* m_neuralEnt;
};