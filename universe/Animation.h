#pragma once

#include <vector>

#include "Timer.h"
#include "TextureSprite.h"

class Animation;
class AnimationShard;

typedef void (*AnimationShardFinishedCb)(AnimationShard* anim, void* userdata);

class AnimationStage
{
public:
	AnimationStage() = delete;
	AnimationStage(int col, int row, int ticks) : textureCol(col), textureRow(row), ticks(ticks) {}

	int textureCol;
	int textureRow;
	int ticks;
};

// A shard is just an instance of the animation with its own timer, properties, etc.
// This is so we don't duplicate loading the same sprite textures over and over
class AnimationShard
{
public:
	AnimationShard() = delete;
	AnimationShard(Animation* parentAnim) :
		m_parent(parentAnim),
		m_currentStage(0U), m_changeTimer(), m_stages(), 
		m_cb(std::make_pair(nullptr, nullptr)) {}

	// I want to be able to reset animations on the fly
	// It isn't like they'll always be in use, they're only ever updated on render
	// but if a shard is mid-anim last time it stopped being used, it'll look off
	void Reset();

	void AddStage(int col, int row, int ticks);
	void SetCallback(AnimationShardFinishedCb cb, void* userdata) { m_cb = std::make_pair(cb, userdata); }
	void Render(int x, int y);

private:
	unsigned int GetLastFrame()
	{
		return m_stages.size() - 1;
	}

	bool IsFinalFrame()
	{
		return m_currentStage == GetLastFrame();
	}

	Animation* m_parent;

	unsigned int m_currentStage;

	Timer m_changeTimer;
	std::vector<AnimationStage> m_stages;
	std::pair<AnimationShardFinishedCb, void*> m_cb;
};

class Animation
{
public:
	Animation() = delete;
	Animation(TextureSprite* sprite);

	AnimationShard* CreateShard()
	{
		return new AnimationShard(this);
	}

	TextureSprite* GetTextureSprite() { return m_sprite; }

private:
	TextureSprite* m_sprite;
};