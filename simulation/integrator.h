#ifndef __INTEGRATOR_H__
#define __INTEGRATOR_H__

void eulerStep(void (*dynFun)(double, double[], double[]),double t0, double t1, double z0[], double z1[], int nDim);

void eulerSim(void (*dynFun)(double, double[], double[]),double t0, double t1, double z0[], double z1[], int nDim, int nStep);

#endif