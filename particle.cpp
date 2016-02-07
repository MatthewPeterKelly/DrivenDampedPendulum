#include "particle.h"


/******************************************************************************
 *                              Private Methods                               *
 ******************************************************************************/

void Particle::timeStepParticle(void) {

	double dt = 2*M_PI/nSubStep;
	double dq = w;   
	double dw = cos(t) - 0.1*w - sin(q);  // Dynamics

	t = t + dt;
	q = q + dt * dq;
	w = w + dt * dw;

}

void Particle::printInitialState(void) {
	printf("Count:  %3d,  Angle:  %6.4f,  Rate:  %6.4f\n",k,q0,w0);
}


/******************************************************************************
 *                              Public Methods                                *
 ******************************************************************************/

void Particle::initialize(void){

	// Initialize the random number generator
	srand((unsigned)time(NULL));

}


Particle::Particle(void) {

	q0 = ((double)rand() / (double)RAND_MAX);
	w0 = ((double)rand() / (double)RAND_MAX);

	/// Scale to desired bounds:
	q0 = q0_low + (q0_upp - q0_low) * q0;
	w0 = w0_low + (w0_upp - w0_low) * w0;

	// Copy to the current state:
	t = t0;
	q = q0;
	w = w0;
}

/* Simulates particle. If the simulation converges, then return true and
 * print the initial state */
bool Particle::simulateOnePeriod(void){

	// Simulation
	for (int i=0; i<nSubStep; i++){
		timeStepParticle();
	}
	k = k+1;  // Counter for number of periods

	// Project back to central basin:
	double basin = (q+M_PI)/(2*M_PI);  // basin edges now at ... -2,-1,0,1,1,2, ... 
	double shift = -2*M_PI*floor(basin);   // Shift required to map to [-pi,pi]
	q0 = q0 + shift;
	q = q + shift;

	// Check if in basin of attraction:
	bool flagInBasin = (q-qCenter)*(q-qCenter) + (w-wCenter)*(w-wCenter) < criticalRadius*criticalRadius;
	if (flagInBasin){
		printInitialState();
	}
	return flagInBasin;

}


void Particle::printState(void) {
	printf("Time:  %6.4f,  Angle:  %6.4f,  Rate:  %6.4f\n",t,q,w);
}



