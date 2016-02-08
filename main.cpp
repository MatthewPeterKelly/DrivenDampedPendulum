#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <random>
#include <stdio.h>

using namespace std;

#include "particle.h"

Particle* particle;

int main()
{

	Particle::initialize();
	particle = new Particle();
	particle->printStateLog();

	// Simulation:
	for (int i = 0; i < 250; i++) {
		particle->timeStep();
		particle->printStateLog();
	};

	return 0;
}