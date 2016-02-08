#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "integrator.h"

int main()
{
	double t0 = 0.0;
	double t1 = 5.0;
	double z0[2];
	double z1[2];
	int nDim = 2;
	int nStep = 200;

	z0[0] = 0.2;
	z0[1] = -0.5;

	eulerSim(t0, t1, z0, z1, nDim, nStep);

}

