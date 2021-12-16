#include "NeuralEntity.h"

NeuralEntity* NeuralEntity::Create(Genome& genome)
{
	NeuralEntity* pNewEntity = new NeuralEntity;

	pNewEntity->m_genome = genome;

	//

	return nullptr;
}

NeuralEntity* NeuralEntity::Create(NeuralEntity** contributors, size_t numberOfContributors)
{
	return nullptr;
}