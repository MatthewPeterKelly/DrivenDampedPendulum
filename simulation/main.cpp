#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

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


int main()
{
	double t0 = 0.0;
	double t1 = 15.0;
	double z0[2];
	double z1[2];
	int nDim = 2;
	int nStep = 50;
	DynFun dynFun = dynamicsFunction;

	z0[0] = 0.2;
	z0[1] = -0.5;

	IntegrationMethod method = RungeKutta;
	simulate(dynFun, t0, t1, z0, z1, nDim, nStep, method);

}

