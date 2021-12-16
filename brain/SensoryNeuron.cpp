#include "SensoryNeuron.h"

void SensoryNeuron::Feed(float data)
{
	for (auto& an : m_axonConnections)
	{
		Neuron* dest = an.GetDestination();

		dest->Feed(data);
	}
}