#pragma once

#include <vector>
#include "SensoryNeuron.h"

class Sensor
{
public:
	Sensor() = delete;
	Sensor(size_t numberOfInputs);

	void Feed(float* data);

	std::vector<SensoryNeuron*>& GetSensoryNeurons() { return m_neurons; }

private:
	std::vector<SensoryNeuron*> m_neurons;
};