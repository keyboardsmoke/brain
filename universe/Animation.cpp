#include "Animation.h"

Animation::Animation(TextureSprite* sprite) : m_sprite(sprite)
{

}

void AnimationShard::Reset()
{
	/*
	m_currentStage = 0U;

	if (m_stages.empty())
		return;

	// m_changeTimer.Start(m_stages[m_currentStage].ticks);*/
}

void AnimationShard::AddStage(int col, int row, int ticks)
{
	m_stages.emplace_back(col, row, ticks);
}

void AnimationShard::Render(int x, int y)
{
	const unsigned int currentTick = SDL_GetTicks();

	// Some not at all needed optimizations
	if (m_stages.empty())
		return;

	if (m_stages.size() == 1)
	{
		m_parent->GetTextureSprite()->RenderFrame(x, y, m_stages[0].textureCol, m_stages[0].textureRow);

		if (!m_changeTimer.IsStarted())
		{
			printf("Not started.\n");

			m_changeTimer.Start(m_stages[0].ticks);
			m_changeTimer.SetFinishedCallback([](void* userdata) -> void
			{
				printf("Single changeTimer cb\n");

				AnimationShard* s = reinterpret_cast<AnimationShard*>(userdata);

				if (s->m_cb.first != nullptr) { s->m_cb.first(s, s->m_cb.second); }
			});
		}
		else
		{
			printf("Running timer...\n");

			m_changeTimer.Run(this);
		}

		return;
	}

	// Here's the meat
	unsigned int nextStage = m_currentStage + 1;

	AnimationStage& stage = m_stages[m_currentStage];

	// Play what we've got
	m_parent->GetTextureSprite()->RenderFrame(x, y, stage.textureCol, stage.textureRow);

	if (m_currentStage == 0U && m_changeTimer.IsStarted() == false)
	{
		m_changeTimer.Start(stage.ticks);
	}

	m_changeTimer.Run(nullptr);

	// We're not doing anything
	if (!m_changeTimer.IsFinished())
		return;

	// We rendered the final frame of the animation
	if (IsFinalFrame())
	{
		if (m_cb.first != nullptr)
		{
			m_cb.first(this, m_cb.second);
		}

		nextStage = 0U;
	}

	// We're switching to a new animation
	m_currentStage = nextStage;

	m_changeTimer.Start(m_stages[m_currentStage].ticks);
}