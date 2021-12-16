#include "Animation.h"

Animation::Animation(TextureSprite* sprite) : m_sprite(sprite)
{

}

void AnimationShard::Reset()
{
	// Just set it up new again
	SetupWorkingStages();
}

void AnimationShard::Tick()
{
	// Do nothing
	if (m_stages.empty())
		return;

	const uint32_t currentTick = SDL_GetTicks();

	if (m_workingStages.empty())
	{
		SetupWorkingStages();
	}

	AnimationStage& currentStage = m_workingStages.front();

	// If the ticks equals or exceeds the stored tick, it's finished
	uint32_t storedRefreshTime = currentStage.ticks;

	if (storedRefreshTime < currentTick)
	{
		// Remove the first entry when the time is exceeded
		m_workingStages.erase(m_workingStages.begin());

		if (m_workingStages.empty())
		{
			// We're finished, callback
			if (m_cb.first != nullptr)
			{
				m_cb.first(this, m_cb.second);
			}

			// We should fill the working stages again here though
			SetupWorkingStages();
		}
	}
}

void AnimationShard::Render(int x, int y)
{
	// Nothing to do
	if (m_workingStages.empty())
		return;

	AnimationStage& stage = m_workingStages.front();

	// Play what we've got
	m_parent->GetTextureSprite()->RenderFrame(x, y, stage.textureCol, stage.textureRow);
}

void AnimationShard::AddStage(int col, int row, int ticks)
{
	m_stages.emplace_back(col, row, ticks);
}

void AnimationShard::SetupWorkingStages()
{
	m_workingStages.clear();

	const uint32_t currentTick = SDL_GetTicks();

	m_workingStages.reserve(m_stages.size());

	uint32_t offset = 0u;

	for (auto& e : m_stages)
	{
		const uint32_t stageTime = currentTick + e.ticks + offset;

		m_workingStages.emplace_back(e.textureCol, e.textureRow, stageTime);

		offset += e.ticks;
	}
}