#include "Brain.h"
#include "Random.h"

Sensor* Brain::AddSensor(size_t numberOfInputs)
{
	return m_sensors.emplace_back(new Sensor(numberOfInputs));
}

Layer* Brain::AddLayer(size_t numberOfNeurons)
{
	//

	return nullptr;
}

Action* Brain::AddAction()
{
	return nullptr;
}

bool Brain::InitializeConnections()
{
	// We need to connect from end to start, because... it's easier? lol

	for (Action* act : m_actions)
	{
		//
	}

	for (Sensor* sensor : m_sensors)
	{
		for (SensoryNeuron* sn : sensor->GetSensoryNeurons())
		{
			const float weight = Random::Real(-1.0f, 1.0f);

			sn->GetAxonConnections().emplace_back(weight, nullptr);
		}
	}

	return false;
}