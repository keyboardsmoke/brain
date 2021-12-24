#pragma once

#include <vector>

#include "Neuron.h"
#include "SensoryNeuron.h"
#include "Interneuron.h"
#include "MotorNeuron.h"

#include "Sensor.h"
#include "Layer.h"
#include "Action.h"

class Brain
{
public:
	Sensor* AddSensor(size_t numberOfInputs);
	Layer* AddLayer(size_t numberOfNeurons);
	Action* AddAction();

	bool InitializeConnections();

private:
	std::vector<Sensor*> m_sensors;
	std::vector<Layer*> m_layers;
	std::vector<Action*> m_actions;
};