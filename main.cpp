#include <stdlib.h>
#include <iostream>
#include <random>

using namespace std;

#include "particle.h"

Particle* particle;

int main()
{
	Particle::initialize();

	// Particles
	particle = new Particle();
	bool flagSuccess;
	for (int i=0; i<1000; i++){
	flagSuccess = particle->simulateOnePeriod();
		if (flagSuccess){
			break;
		}
	}
	if (!flagSuccess){
		cout << "Fail! \n";
	}

   return 0;
}