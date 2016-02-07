#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#define _USE_MATH_DEFINES // M_PI
#include <math.h>

#include <stdlib.h>
#include <iostream>

#include <random>   // RNG
#include <chrono>   // For initializing the RNG

using namespace std;

class Particle {

private:

	/// Bounds on initial state for random initialization
	double q0_low = -M_PI;
	double q0_upp = M_PI;
	double w0_low = -5.0;
	double w0_upp = 5.0;

	/// Initial state of a particle:
	double t0 = 0.0;
	double q0; 	// initial angle
	double w0; 	// initial rate

	/// Current state of a particle
	double t;	// time
	double q;  	// angle
	double w;  	// rate
	int k = 0;   // number of periods 

	/// How many time steps to use for each period of the forcing function:
	int nSubStep = 20;

	/// Center of attraction in the first basin:
	double qCenter = -2.0463;   // angle
	double wCenter = 0.3927;  // rate
	double criticalRadius = 0.1;  // radius of convergence in phase space

	/// Simulate the system forward by one time step:
	void timeStepParticle(void);

	/// Prints the initial state of the trajectory:
	void printInitialState(void);

public:
	static void initialize(void);  // Computes all shared data  

	Particle(void);  // Creates a new particle

	bool simulateOnePeriod(void);  // simulates a single period of the forcing function

	void printState(void);  // Prints the current state of the particle


};


#endif