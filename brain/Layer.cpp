#include "Layer.h"

Layer::Layer(size_t numberOfNeurons)
{
	m_neurons.resize(numberOfNeurons);

	for (size_t i = 0; i < m_neurons.size(); ++i)
	{
		m_neurons[i] = new InterNeuron;
	}
}

void Layer::Feed(float* data)
{
	for (auto& sn : m_neurons)
	{
		sn->Feed(*data);

		++data;
	}
}