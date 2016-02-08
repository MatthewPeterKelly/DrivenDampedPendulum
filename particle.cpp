#include "particle.h"


/******************************************************************************
 *                              Private Methods                               *
 ******************************************************************************/

/* Integrate forward using Runge-Kutta method */
void Particle::timeStep(void) {

	double dt = 2*M_PI/nSubStep;
	double dqLow = w;   
	double dwLow = cos(t) - 0.1*w - sin(q);  // Dynamics

	double tMid = t + 0.5*dt;
	double qMidA = q + 0.5*dt * dqLow;
	double wMidA = w + 0.5*dt * dwLow;
	double dqMidA = wMidA;
	double dwMidA = cos(tMid) - 0.1*wMidA - sin(qMidA);  // Dynamics

	double	qMidB = q + dt*dqMidA;
	double	wMidB = w + dt*dwMidA;
	double dqMidB = wMidB;
	double dwMidB = cos(tMid) - 0.1*wMidB - sin(qMidB);  // Dynamics

	double tUpp = t + dt;
	double qUpp = q + dt*dqMidB;
	double wUpp = w + dt*dwMidB;
	double dqUpp = wUpp;
	double dwUpp = cos(tUpp) - 0.1*wUpp - sin(qUpp);  // Dynamics

	t = tUpp;
	q = q + (dt/6)*(dqLow + 2.0*dqMidA + 2.0*dqMidB + dqUpp);
	w = w + (dt/6)*(dwLow + 2.0*dwMidA + 2.0*dwMidB + dwUpp);

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

// /* Simulates particle. If the simulation converges, then return true and
//  * print the initial state */
// bool Particle::simulateOnePeriod(void){

// 	// Simulation
// 	for (int i=0; i<nSubStep; i++){
// 		timeStepParticle();
// 	}
// 	k = k+1;  // Counter for number of periods

// 	// Project back to central basin:
// 	double basin = (q+M_PI)/(2*M_PI);  // basin edges now at ... -2,-1,0,1,1,2, ... 
// 	double shift = -2*M_PI*floor(basin);   // Shift required to map to [-pi,pi]
// 	double qShift = q + shift;

// 	// Check if in basin of attraction:
// 	bool flagInBasin = (qShift-qCenter)*(qShift-qCenter) + (w-wCenter)*(w-wCenter) < criticalRadius*criticalRadius;
// 	//if (flagInBasin){
// 		// printInitialState();
// 	//}
// 	printState();
// 	return flagInBasin;

// }


void Particle::printState(void) {
	printf("Time:  %6.4f,  Angle:  %6.4f,  Rate:  %6.4f\n",t,q,w);
}



void Particle::printStateLog(){
	printf("%6.4f, %6.4f, %6.4f\n",t,q,w);
}