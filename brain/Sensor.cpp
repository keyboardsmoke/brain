#include "Sensor.h"

Sensor::Sensor(size_t numberOfInputs)
{
	m_neurons.resize(numberOfInputs);
}

void Sensor::Feed(float* data)
{
	for (auto& sn : m_neurons)
	{
		sn->Feed(*data);

		++data;
	}
}