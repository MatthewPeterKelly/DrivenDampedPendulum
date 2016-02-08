#include <iostream>
#include <fstream>
using namespace std;

#include <cmath>

#include "integrator.h"


/* Template dynamics function */
void dynamicsFunction(double t, double z[], double dz[]) {

	double x = z[0];
	double v = z[1];
	double u = cos(t);
	double dx = v;
	double dv = u - 0.1 * v - sin(x);
	dz[0] = dx;
	dz[1] = dv;

}

/* Takes a simple euler step for the system */
void eulerStep(double t0, double t1, double z0[], double z1[], int nDim) {

	double dt = t1 - t0;
	double *dz;
	dz = new double[nDim];

	dynamicsFunction(t0, z0, dz);

	for (int i = 0; i < nDim; i++) {
		z1[i] = z0[i] + dt * dz[i];
	}

	delete [] dz;

}


/* Runs several time steps using euler integration */
void eulerSim(double t0, double t1, double z0[], double z1[], int nDim, int nStep) {
	double dt, tLow, tUpp;
	double *zLow;
	double *zUpp;

	/// Allocate memory:
	zLow = new double[nDim];
	zUpp = new double[nDim];

    /// File IO stuff:
	ofstream logFile;
	logFile.open("logFile.csv");

	/// Initial conditions
	tLow = t0;
	for (int i = 0; i < nDim; i++) {
		zLow[i] = z0[i];
	}

	/// March forward in time:
	dt = (t1 - t0) / ((double) nStep);
	for (int i = 0; i < nStep; i++) {
		tUpp = tLow + dt;
		eulerStep(tLow, tUpp, zLow, zUpp, nDim);

		/// Print the state of the simulation:
		logFile << tLow ;
		for (int j = 0; j < nDim; j++) {
			logFile << ", " << zLow[j];
		}
		logFile << "\n";

		/// Advance temp variables:
		tLow = tUpp;
		for (int j = 0; j < nDim; j++) {
			zLow[j] = zUpp[j];
		}

	}

	delete [] zLow;
	delete [] zUpp;

	logFile.close();

}