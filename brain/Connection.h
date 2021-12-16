#pragma once

class Neuron;

class Connection
{
public:
	Connection() = delete;
	Connection(float weight, Neuron* destination) :
		m_weight(weight), m_dest(destination) {}

	float GetWeight() const { return m_weight; }
	
	void SetWeight(float newWeight) { m_weight = newWeight; }

	Neuron* GetDestination() { return m_dest; }

private:
	float m_weight;
	Neuron* m_dest;
};