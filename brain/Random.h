#pragma once

class Random
{
public:

	static void SetSeed(unsigned seed = 0);
	static unsigned GetSeed();

	template<typename T>
	static T Value()
	{
		T r;
		Bytes(&r, sizeof(T));
		return r;
	}

	template<typename T>
	static T Value(T min, T max)
	{
		return (Random::Value<T>() % (max - min + 1)) + min;
	}

	static void Bytes(void* data, size_t size);
};