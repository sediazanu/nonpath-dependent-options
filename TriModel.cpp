#include "TriModel.h"
#include <cmath>

using namespace std;

/* MEMBER FUNCTIONS IMPLEMENTATIONS */

void TriModel::Set_dtdx(double T, int N)
{
    dt = T/N;
    dx = sigma*sqrt(2*dt);
}

double TriModel::RiskNeutProb_up()
{
    return ((sigma*sigma*dt + nu*nu*dt*dt)/dx/dx + nu*dt/dx)/2;
}

double TriModel::RiskNeutProb_down()
{
    return ((sigma*sigma*dt + nu*nu*dt*dt)/dx/dx - nu*dt/dx)/2;
}

double TriModel::S(int i)
{
    return S0*exp(i*dx);
}
