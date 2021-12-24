#pragma once

// Typical neuron, up to:
// 10,000 recv synapses
// 100,000 output synapses

// 32GB = 32000MB = 32000000KB = 32000000000B

// 1000000000 * 4 = 4 bil
// ~32bil bytes

// 32 byte structure would consume all memory in the system
// roughly half of ram is consumed at all times, sometimes more, sometimes less
// can't count on system resources to be stable, either...

// "We found that on average the human brain has 86 billion neurons. And not one that we looked at so far has 100 billion."
// So, maybe a little bit more leeway here

#include <vector>
#include "Connection.h"

class Neuron
{
public:
	virtual void Feed(float data) = 0;

	std::vector<Connection>& GetAxonConnections() { return m_axonConnections; }
	std::vector<Connection>& GetDendriteConnections() { return m_dendriteConnections; }

protected:
	// Output to connected Neurons
	std::vector<Connection> m_axonConnections;

	// Input from other Neurons
	std::vector<Connection> m_dendriteConnections;
};