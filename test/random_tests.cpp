#include "doctest.h"
#include "Random.h"

TEST_CASE("Random Float")
{
	const float f1 = Random::Real(-1.0f, 1.0f);
	const float f2 = Random::Real(0.0f, 1000.f);

	REQUIRE(f1 >= -1.0f);
	REQUIRE(f1 <= 1.0f);
	REQUIRE(f2 >= 0.0f);
	REQUIRE(f2 <= 1000.f);
}