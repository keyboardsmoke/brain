#pragma once

// Sensory neurons are sensitive to various non-neural stimuli. 
// There are sensory neurons in the skin, muscles, joints, and organs that indicate pressure, temperature, and pain. 
// There are more specialized neurons in the nose and tongue that are sensitive to the molecular shapes we perceive as tastes and smells. 
// Neurons in the inner ear are sensitive to vibration, and provide us with information about sound.
// And the rods and cones of the retina are sensitive to light, and allow us to see.
// Basically, inputs

#include "Neuron.h"

class SensoryNeuron : public Neuron
{
public:
	void Feed(float data) override;

private:
	//
};