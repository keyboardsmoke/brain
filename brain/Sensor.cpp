#include "Sensor.h"

///////////////////////////////////////////////////////////////////////////
// 
// S -< I -< I -< I -< A
// S -< I -< I -< I -< A
// S -< I -< I -< I -< A
// S -< I -< I -< I -< A
// 
///////////////////////////////////////////////////////////////////////////

Sensor::Sensor(size_t numberOfInputs)
{
	m_neurons.resize(numberOfInputs);

	for (size_t i = 0; i < m_neurons.size(); ++i)
	{
		m_neurons[i] = new SensoryNeuron;
	}
}

void Sensor::Feed(float* data)
{
	for (auto& sn : m_neurons)
	{
		sn->Feed(*data);

		++data;
	}
}