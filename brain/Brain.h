#pragma once

#include <vector>

#include "Neuron.h"
#include "SensoryNeuron.h"
#include "Interneuron.h"
#include "MotorNeuron.h"

#include "Sensor.h"

class Brain
{
public:
	Sensor* AddSensor(size_t numberOfInputs);

private:
	std::vector<Sensor*> m_sensors;
};