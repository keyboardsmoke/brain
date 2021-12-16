#include "doctest.h"
#include "Timer.h"

TEST_CASE("Basic timer test")
{
	uint32_t startTicks = SDL_GetTicks();

	Timer t;

	t.SetFinishedCallback([&](void* userdata) -> void
	{
		REQUIRE(SDL_GetTicks() > startTicks + 1000);
	});

	t.Start(1000);

	while (!t.IsFinished())
	{
		t.Run(nullptr);
		
		SDL_Delay(10);
	}
}