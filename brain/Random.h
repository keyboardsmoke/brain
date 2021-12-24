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
	static T Integer(T min, T max)
	{
		return (Random::Value<T>() % (max - min + static_cast<T>(1))) + min;
	}

	static float Real(float min, float max);
	static double Real(double min, double max);

	static void Bytes(void* data, size_t size);
};