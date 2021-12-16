#pragma once

#include "Brain.h"
#include "Genome.h"

class NeuralEntity
{
public:
	// The miracle of... uhh, science doesn't know yet. It just poofed into existence. There.
	static NeuralEntity* Create(Genome& genome);

	// The miracle of birth! With... N partners? Ought to be interesting.
	static NeuralEntity* Create(NeuralEntity** contributors, size_t numberOfContributors);

	// Get the Genome instance
	Genome& GetGenome() { return m_genome; }

	// Get the Brain instance (connected neurons)
	Brain& GetBrain() { return m_brain; }

private:
	Genome m_genome;
	Brain m_brain;
};