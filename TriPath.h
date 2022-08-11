#ifndef TRIPATH_H
#define TRIPATH_H
#include <vector>
#include <cmath>
#include "TriModel.h"
#include "ReadCSVFile.h"

/*  CLASS:  TRIPATH

    The class TriPath is a subclass of TriModel. The purpose of the class is to encode
    all possible paths in a trinomial tree, their associated prices, and their associated
    probabilities.

    You should implement the methods for the path, prices and trees yourself, including
    any functions you deem necessary.
*/

class TriPath : public TriModel
{
private:
    double T;
    int N;
    int h;
public:


    // returns the value of N
    int Get_N()
    {
        return N;
    }

    // returns the value of T
    double Get_T()
    {
        return T;
    }

    //returns the value of h, which is used to go through each of the options

    int Get_h()
    {
        return h;
    }

    TriPath(double S0_, double sigma_, double r_, double T_, int N_, int h_) : TriModel(S0_,sigma_,r_),h(h_)
    {
        N=6;
        T=1;
    };
    void PathByNumber(int x,int *path)
    {
        int pricepath=pow(3,N); //sets the length of the array to 3^N

        int x2 = x;
        for(int i = 1; i <= N; i++)
        {
            if(x2 <= pricepath/3)
            {
                path[i-1]=2; //store a 2 for when the path is heading upwards
                pricepath=pricepath/3;
            }
            else if(x2 <= (2*pricepath)/3)
            {
                path[i-1]=1; //stores a 1 for the path staying in the middle
                pricepath=(2*pricepath)/3;
                x2=x2-(pricepath%x2);
            }
            else
            {
                path[i-1]=0; //stores a 0 when the path is going downwards
                pricepath=pricepath;
                x2=x2-(2*(pricepath%x2));
            }

        }
    }

    void PriceByPath(int *path, double *prices)
    {
        double x = Get_dx(); //obtains the dx value
        prices[0] =Get_S0(); //obtaints the stock price
        double j=0;
        for(int i=0; i<N; i++)
        {
            if(path[i]==0) //reduces the price of the function if the position is 0
            {
                j=j-1;
            }
            if(path[i]==1) //keeps the price the same if the position is in the middle
            {
                j=j;
            }
            if(path[i]==2) //increases the price if the position goes upwards
            {
                j=j+1;
            }
            prices[i+1]=S(j);
        }
    }

    double ProbabilityByPath(int *path)
    {
        double qu =RiskNeutProb_up(); //obtains the probability of using the upwards branch
        double qd= RiskNeutProb_down(); //obtains the probability of using the downwards branch
        double qm = 1-qu-qd; //obtains the probability of using the middle branch
        double prob=1;
        for(int i=0; i<N; i++)
        {
            if(path[i]==0)
            {
                prob=prob*qd; //the probability multiplied by risk neutral probability of going down
            }
            if(path[i]==1)
            {
                prob=prob*qm; //the probability multiplied by risk neutral probability of going in the middle
            }
            if(path[i]==2)
            {
                prob=prob*qu; //the probability multiplied by risk neutral probability of going up
            }

        }
        return prob;
    }


};



#endif // TRIPATH_H
