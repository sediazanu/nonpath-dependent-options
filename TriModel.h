/*  CLASS:  TRIMODEL

    The class TriModel describes the possible evolution of a stock, whose initial value is S0.

    The evolution of a stock can increase, remain the same, or decrease, according to the
    risk neutral probability up, neutral, or down, respectively. These probabilities are
    defined according to sigma, r, nu, dt and dx.

*/


#ifndef TRIMODEL_H
#define TRIMODEL_H
#include <cmath>


class TriModel
{
    private:
        double S0;      // Initial stock price
        double sigma;   // Stock volatility
        double r;       // Continuously compounded interest rate
        double nu;      // Constant, used in calculations
        double dt;      // Time interval (time step size)
        double dx;      // Stock interval (stock step size)

    public:
        // Constructor to initialise data members
        TriModel(double S0_, double sigma_,double r_): S0(S0_), sigma(sigma_),r(r_)
        {
            nu = r-sigma*sigma/2.0;

            dt = 1.0/6.0;
            dx = sigma*sqrt(2*dt);
        }

        // member function to set values of dt and dx
        // T maturity of the option, N number of time steps
        void Set_dtdx(double T, int N);

        // calculate the risk neutual probability of going up
        double RiskNeutProb_up();

        // calculate the risk neutual probability of going down
        double RiskNeutProb_down();

        // calculate the stock price at time step n and node i
        double S(int i);

        // return the risk free interest rate R
        double Get_r() { return r;}

        // return time interval dt
        double Get_dt() { return dt;}

        //return the stock price s0
        double Get_S0() {return S0;}

        //gets the value of dx
        double Get_dx() {return dx;}
};




#endif // TRIMODEL_H


