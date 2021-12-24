#pragma once

#include "InterNeuron.h"

class Layer
{
public:
	Layer() = delete;
	Layer(size_t numberOfNeurons);

	void Feed(float* data);

private:
	std::vector<InterNeuron*> m_neurons;
};