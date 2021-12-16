#include "Random.h"
#include <random>
#include <algorithm>
#include <functional>
#include <chrono>

#include "PointerContainer.h"

unsigned currentSeed = 0u;

std::random_device r;
std::default_random_engine randomEngine(r());
std::uniform_int_distribution<int> uniformDist(CHAR_MIN, CHAR_MAX);

void Random::SetSeed(unsigned seed)
{
    if (seed != 0)
    {
        currentSeed = seed;   
    }
    else
    {
        auto n = std::chrono::system_clock::now();
        auto c = std::chrono::system_clock::to_time_t(n);

        currentSeed = static_cast<unsigned>(c);
    }

    randomEngine.seed(currentSeed);
}

unsigned Random::GetSeed()
{
    return currentSeed;
}

void Random::Bytes(void* data, size_t size)
{
    pointer_container<uint8_t> p(reinterpret_cast<uint8_t*>(data), size);
    std::generate(p.begin(), p.end(), []() {
        return uniformDist(randomEngine);
    });
}